#include "updatechecker.h"
#include "roninversion.h"

#include <array>
#include <charconv>
#include <chrono>
#include <optional>
#include <string_view>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace
{

using Version = std::array<unsigned, 3>;
using Clock = std::chrono::steady_clock;

std::optional<Version> ParseVersion(std::string_view text)
{
	if (text.starts_with('v'))
		text.remove_prefix(1);

	Version version{};
	for (size_t i = 0; i < version.size(); ++i)
	{
		if (text.empty() || text.front() < '0' || text.front() > '9')
			return std::nullopt;
		const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), version[i]);
		if (error != std::errc{} || (end - text.data() > 1 && text.front() == '0'))
			return std::nullopt;
		text.remove_prefix(end - text.data());
		if (i + 1 < version.size())
		{
			if (text.empty() || text.front() != '.')
				return std::nullopt;
			text.remove_prefix(1);
		}
	}
	return text.empty() ? std::optional(version) : std::nullopt;
}

struct UpdateChecker
{
	CURL* request = nullptr;
	CURLM* transfers = nullptr;
	bool attached = false;
	std::string response;
	std::string latestVersion;
	const char* state = "idle";
	Clock::time_point nextCheck{};

	void Close()
	{
		if (attached)
			curl_multi_remove_handle(transfers, request);
		if (request)
			curl_easy_cleanup(request);
		if (transfers)
			curl_multi_cleanup(transfers);
		request = nullptr;
		transfers = nullptr;
		attached = false;
	}

	void ReadRelease(std::string_view installed)
	{
		const auto release = nlohmann::json::parse(response, nullptr, false);
		if (!release.is_object() || !release.contains("tag_name") || !release["tag_name"].is_string()
			|| !release.contains("draft") || release["draft"] != false
			|| !release.contains("prerelease") || release["prerelease"] != false)
			return;

		const auto tag = release["tag_name"].get<std::string>();
		const auto latest = ParseVersion(tag);
		if (!latest)
			return;
		latestVersion = tag;
		const auto current = ParseVersion(installed);
		state = !current ? "development" : *latest > *current ? "available" : "current";
	}
};

UpdateChecker checker;

size_t ReceiveRelease(char* data, size_t size, size_t count, void* context) noexcept
{
	auto& response = *static_cast<std::string*>(context);
	constexpr size_t maxSize = 256 * 1024;
	if (size != 0 && count > (maxSize - response.size()) / size)
		return 0;
	const size_t bytes = size * count;
	try
	{
		response.append(data, bytes);
		return bytes;
	}
	catch (...)
	{
		return 0;
	}
}

}

void UpdateChecker_Start()
{
	if (checker.request || Clock::now() < checker.nextCheck)
		return;
	checker.nextCheck = Clock::now() + std::chrono::seconds(60);
	checker.state = "unavailable";
	checker.response.clear();
	checker.latestVersion.clear();
	if (!(curl_version_info(CURLVERSION_NOW)->features & CURL_VERSION_ASYNCHDNS))
		return;

	checker.request = curl_easy_init();
	checker.transfers = curl_multi_init();
	if (!checker.request || !checker.transfers
		|| curl_easy_setopt(checker.request, CURLOPT_URL, "https://api.github.com/repos/TF2SR/Ronin/releases/latest") != CURLE_OK
		|| curl_easy_setopt(checker.request, CURLOPT_USERAGENT, "Ronin-UpdateChecker") != CURLE_OK
		|| curl_easy_setopt(checker.request, CURLOPT_PROTOCOLS_STR, "https") != CURLE_OK
		|| curl_easy_setopt(checker.request, CURLOPT_CONNECTTIMEOUT_MS, 5000L) != CURLE_OK
		|| curl_easy_setopt(checker.request, CURLOPT_TIMEOUT_MS, 10000L) != CURLE_OK
		|| curl_easy_setopt(checker.request, CURLOPT_NOSIGNAL, 1L) != CURLE_OK
		|| curl_easy_setopt(checker.request, CURLOPT_WRITEFUNCTION, ReceiveRelease) != CURLE_OK
		|| curl_easy_setopt(checker.request, CURLOPT_WRITEDATA, &checker.response) != CURLE_OK
		|| curl_multi_add_handle(checker.transfers, checker.request) != CURLM_OK)
	{
		checker.Close();
		return;
	}
	checker.attached = true;
	checker.state = "checking";
}

const char* UpdateChecker_Poll()
{
	if (!checker.request)
		return checker.state;

	int running = 0;
	if (curl_multi_perform(checker.transfers, &running) == CURLM_OK)
	{
		int remaining = 0;
		while (const auto message = curl_multi_info_read(checker.transfers, &remaining))
		{
			if (message->msg != CURLMSG_DONE)
				continue;
			checker.state = "unavailable";
			long status = 0;
			if (message->data.result == CURLE_OK
				&& curl_easy_getinfo(checker.request, CURLINFO_RESPONSE_CODE, &status) == CURLE_OK && status == 200)
			{
				try
				{
					checker.ReadRelease(RONIN_VERSION);
				}
				catch (...)
				{
					checker.state = "unavailable";
				}
			}
			checker.Close();
			return checker.state;
		}
		if (running)
			return checker.state;
	}
	checker.state = "unavailable";
	checker.Close();
	return checker.state;
}

const std::string& UpdateChecker_LatestVersion()
{
	return checker.latestVersion;
}

void UpdateChecker_Shutdown()
{
	checker.Close();
}
