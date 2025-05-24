#include "core/stdafx.h"
#include "core/logdef.h"

std::shared_ptr<spdlog::logger> g_TermLogger;
std::shared_ptr<spdlog::logger> g_GameLogger;

//#############################################################################
// SPDLOG INIT
//#############################################################################
void SpdLog_Init(void)
{
	static bool bInitialized = false;

	if (bInitialized)
	{
		Assert(bInitialized, "'SpdLog_Init()' has already been called.");
		return;
	}

#ifndef NETCONSOLE
	char appdata[MAX_PATH];
	GetEnvironmentVariableA("APPDATA", appdata, MAX_PATH);
	g_LogSessionDirectory = fmt::format("{:s}\\ronin\\logs\\{:s}", appdata, g_ProcessTimestamp);
	/************************
	 * GAME CONSOLE LOGGER SETUP   *
	 ************************/
	{
		g_GameLogger = std::make_shared<spdlog::logger>("game_console", g_LogSink);
		spdlog::register_logger(g_GameLogger); // in-game console logger.
		g_GameLogger->set_pattern("[%H:%M:%S] %v");
		g_GameLogger->set_level(spdlog::level::trace);
	}
#endif // !NETCONSOLE
	/************************
	 * WINDOWS LOGGER SETUP *
	 ************************/
	{
		g_TermLogger = spdlog::stdout_logger_mt("win_console");

		// Determine if user wants ansi-color logging in the terminal.
		g_TermLogger->set_pattern("[%H:%M:%S] %v\u001b[0m");
		g_bSpdLog_UseAnsiClr = true;
		//g_TermLogger->set_level(spdlog::level::trace);
	}

#ifndef NETCONSOLE
	spdlog::set_default_logger(g_TermLogger); // Set as default.
	SpdLog_Create();
#endif // !NETCONSOLE

	spdlog::set_level(spdlog::level::trace);
	bInitialized = true;
}

void SpdLog_Create()
{
	/************************
	 * ROTATE LOGGER SETUP  *
	 ************************/
	spdlog::basic_logger_mt<spdlog::synchronous_factory>("log", fmt::format("{:s}\\{:s}", g_LogSessionDirectory, "log.log"))->set_pattern("[%Y-%m-%d %H:%M:%S.%e] %v");
}

//#############################################################################
// SPDLOG POST INIT
//#############################################################################
void SpdLog_PostInit()
{
#ifndef NETCONSOLE
	spdlog::flush_every(std::chrono::seconds(5)); // Flush buffers every 5 seconds for every logger.
	g_GameLogger->set_pattern("%v");
#endif // !NETCONSOLE

	g_TermLogger->set_pattern("%v\u001b[0m");
	g_bSpdLog_UseAnsiClr = true;
	g_bSpdLog_PostInit = true;
	g_bLogToGameConsole = true;
}

//#############################################################################
// SPDLOG SHUTDOWN
//#############################################################################
void SpdLog_Shutdown()
{
	spdlog::shutdown();
}
