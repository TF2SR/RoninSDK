#pragma once
#if defined(_DEBUG) || defined(_PROFILE)
#pragma message ("Profiling is turned on; do not release this binary!\n")
#endif // _DEBUG || _PROFILE

#define WIN32_LEAN_AND_MEAN // Prevent winsock2 redefinition.
#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <bcrypt.h>
#include <comdef.h>
#include <direct.h>
#include <gdiplus.h>
#include <dbghelp.h>
#include <timeapi.h>
#include <shellapi.h>
#include <Psapi.h>
#include <setjmp.h>
#include <tchar.h>
#include <stdio.h>
#include <shlobj.h>
#include <objbase.h>
#include <intrin.h>
#include <emmintrin.h>
#include <cmath>
#include <regex>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <filesystem>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include <smmintrin.h>

// Windows specifics.
#ifndef FILE_SUPPORTS_GHOSTING
#define FILE_SUPPORTS_GHOSTING 0x40000000  // winnt
#endif
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#if !defined(DEDICATED) && !defined(SDKLAUNCHER) && !defined (NETCONSOLE) && !defined(PLUGINSDK)
#include <d3d11.h>
#endif // !DEDICATED && !SDKLAUNCHER && !NETCONSOLE && !PLUGINSDK

#include <nlohmann/json.hpp>

#include "thirdparty/detours/detours.h"
#include "thirdparty/detours/idetour.h"


#if !defined(SDKLAUNCHER) && !defined (NETCONSOLE) && !defined(PLUGINSDK)
//#include "thirdparty/lzham/include/lzham_assert.h"
//#include "thirdparty/lzham/include/lzham_types.h"
//#include "thirdparty/lzham/include/lzham.h"
#endif // !SDKLAUNCHER && !NETCONSOLE && !PLUGINSDK

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <curl/curl.h>

#include "common/experimental.h"
#include "common/pseudodefs.h"
#include "common/x86defs.h"
#include "common/sdkdefs.h"

#include "public/utility/utility.h"
#include "public/utility/memaddr.h"
#include "public/utility/module.h"
//#include "public/utility/vdf_parser.h"

#include "core/assert.h"
#include "core/termutil.h"
#include "core/init.h"
#include "tier0/basetypes.h"
#include "tier0/platform.h"
#include "tier0/annotations.h"
#include "tier0/commonmacros.h"
#if !defined(SDKLAUNCHER) && !defined(PLUGINSDK)
#include "tier0/dbg.h"
#endif // !SDKLAUNCHER && !NETCONSOLE && !PLUGINSDK

#undef GetCurrentDirectory

#define REGISTER_MODULE(strModule)                                  \
	if(AllocateModule(strModule))                                   \
	{                                                               \
		DetourScanModule(strModule);                                \
		DetourAttachModule(strModule);                              \
	}                                                               \

#define SCAN_MODULE(loadedModule, wantedModule, global)             \
	if (loadedModule == #wantedModule && !global)                   \
	{                                                               \
		global = new CModule(#wantedModule);                        \
		if (!global->Good())                                        \
		{                                                           \
            delete global;                                          \
			global = nullptr;                                       \
			return false;                                           \
		}                                                           \
		return true;                                                \
	}                                                               \

inline CModule* g_pSDKDll = nullptr;
inline CModule* g_pLauncherDll = nullptr;
inline CModule* g_pTier0Dll = nullptr;
inline CModule* g_pEngineDll = nullptr;
inline CModule* g_pClientDll = nullptr;
inline CModule* g_pServerDll = nullptr;
inline CModule* g_pFSStdioDll = nullptr; // filesystem_stdio.dll
inline CModule* g_pMatSys_DX11Dll = nullptr;

inline const string g_ProcessTimestamp = CreateTimedFileName();


#define VAR_NAME(varName)  #varName

#define MEMBER_AT_OFFSET(varType, varName, offset)             \
	varType& varName()                                         \
	{                                                          \
		static int _##varName = offset;                        \
		return *(varType*)((std::uintptr_t)this + _##varName); \
	}

template <typename ReturnType, typename ...Args>
ReturnType CallVFunc(int index, void* thisPtr, Args... args)
{
	return (*reinterpret_cast<ReturnType(__fastcall***)(void*, Args...)>(thisPtr))[index](thisPtr, args...);
}

inline void LogFunAdr(const char* szFun, uintptr_t nAdr) // Logging function addresses.
{
	spdlog::debug("| {:s}: {:42s}: {:#18x} |\n", "FUN", szFun, nAdr);
}
inline void LogVarAdr(const char* szVar, uintptr_t nAdr) // Logging variable addresses.
{
	spdlog::debug("| {:s}: {:42s}: {:#18x} |\n", "VAR", szVar, nAdr);
}
inline void LogConAdr(const char* szCon, uintptr_t nAdr) // Logging constant addresses.
{
	spdlog::debug("| {:s}: {:42s}: {:#18x} |\n", "CON", szCon, nAdr);
}
//#endif // !SDKLAUNCHER && !NETCONSOLE && !PLUGINSDK
