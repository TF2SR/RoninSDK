#include "windows/loadlibrary.h"

///////////////////////////////////////////////////////////////////////////////
typedef HMODULE(WINAPI* ILoadLibraryExA)(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
typedef HMODULE(WINAPI* ILoadLibraryExW)(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
typedef HMODULE(WINAPI* ILoadLibraryA)(LPCSTR lpLibFileName);
typedef HMODULE(WINAPI* ILoadLibraryW)(LPCWSTR lpLibFileName);

///////////////////////////////////////////////////////////////////////////////
static ILoadLibraryExA            g_oLoadLibraryExA = nullptr;
static ILoadLibraryExW            g_oLoadLibraryExW = nullptr;
static ILoadLibraryA              g_oLoadLibraryA = nullptr;
static ILoadLibraryW              g_oLoadLibraryW = nullptr;

///////////////////////////////////////////////////////////////////////////////

void LoadLibrary_Setup()
{
	g_oLoadLibraryExA = (ILoadLibraryExA)DetourFindFunction("Kernel32.dll", "LoadLibraryExA");
	g_oLoadLibraryExW = (ILoadLibraryExW)DetourFindFunction("Kernel32.dll", "LoadLibraryExW");
	g_oLoadLibraryA = (ILoadLibraryA)DetourFindFunction("Kernel32.dll", "LoadLibraryA");
	g_oLoadLibraryW = (ILoadLibraryW)DetourFindFunction("Kernel32.dll", "LoadLibraryW");
}

HMODULE WINAPI HLoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	HMODULE hLibrary = g_oLoadLibraryExA(lpLibFileName, hFile, dwFlags);
	fs::path libPath = fs::path(lpLibFileName);
	std::string libName = libPath.filename().string();
	REGISTER_MODULE(libName.c_str());
	//DevMsg(eDLL_T::NONE, "HLoadLibraryExA: %s\n", libName.c_str());
	return hLibrary;
}

HMODULE WINAPI HLoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	HMODULE hLibrary = g_oLoadLibraryExW(lpLibFileName, hFile, dwFlags);
	fs::path libPath = fs::path(lpLibFileName);
	std::string libName = libPath.filename().string();
	REGISTER_MODULE(libName.c_str());
	//DevMsg(eDLL_T::NONE, "HLoadLibraryExW: %s\n", libName.c_str());
	return hLibrary;
}

HMODULE WINAPI HLoadLibraryA(LPCSTR lpLibFileName)
{
	HMODULE hLibrary = g_oLoadLibraryA(lpLibFileName);
	fs::path libPath = fs::path(lpLibFileName);
	std::string libName = libPath.filename().string();
	REGISTER_MODULE(libName.c_str());
	//DevMsg(eDLL_T::NONE, "HLoadLibraryA: %s\n", libName.c_str());
	return hLibrary;
}

HMODULE WINAPI HLoadLibraryW(LPCWSTR lpLibFileName)
{
	HMODULE hLibrary = g_oLoadLibraryW(lpLibFileName);
	fs::path libPath = fs::path(lpLibFileName);
	std::string libName = libPath.filename().string();
	REGISTER_MODULE(libName.c_str());
	//DevMsg(eDLL_T::NONE, "HLoadLibraryW: %s\n", libName.c_str());
	return hLibrary;
}

void LoadLibrary_Init()
{
	LoadLibrary_Setup();

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	///////////////////////////////////////////////////////////////////////////
	DetourAttach(&(LPVOID&)g_oLoadLibraryExA, (PBYTE)HLoadLibraryExA);
	DetourAttach(&(LPVOID&)g_oLoadLibraryExW, (PBYTE)HLoadLibraryExW);
	DetourAttach(&(LPVOID&)g_oLoadLibraryA, (PBYTE)HLoadLibraryA);
	DetourAttach(&(LPVOID&)g_oLoadLibraryW, (PBYTE)HLoadLibraryW);

	///////////////////////////////////////////////////////////////////////////
	HRESULT hr = DetourTransactionCommit();
	if (hr != NO_ERROR)
	{
		// Failed to hook into the process, terminate
		Error(eDLL_T::COMMON, 0xBAD0C0DE, "Failed to detour process: error code = %08x\n", hr);
	}
}

void LoadLibrary_Shutdown()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	///////////////////////////////////////////////////////////////////////////
	DetourDetach(&(LPVOID&)g_oLoadLibraryExA, (PBYTE)HLoadLibraryExA);
	DetourDetach(&(LPVOID&)g_oLoadLibraryExW, (PBYTE)HLoadLibraryExW);
	DetourDetach(&(LPVOID&)g_oLoadLibraryA, (PBYTE)HLoadLibraryA);
	DetourDetach(&(LPVOID&)g_oLoadLibraryW, (PBYTE)HLoadLibraryW);

	///////////////////////////////////////////////////////////////////////////
	DetourTransactionCommit();
}
