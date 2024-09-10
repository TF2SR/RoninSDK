#include "core/stdafx.h"
#include "core/r2dev.h"
#include "core/init.h"
#include "core/logdef.h"

#include "windows/console.h"
#include "windows/loadlibrary.h"

void SDK_Init()
{
    g_svCmdLine = GetCommandLineA();

#ifndef DEDICATED
    if (g_svCmdLine.find("-wconsole") != std::string::npos)
    {
        Console_Init();
    }
#else
    Console_Init();
#endif // !DEDICATED

    curl_global_init(CURL_GLOBAL_ALL);

    SpdLog_Init();

    for (size_t i = 0; i < SDK_ARRAYSIZE(R2SDK_EMBLEM); i++)
    {
        string svEscaped = StringEscape(R2SDK_EMBLEM[i]);
        spdlog::info("{:s}{:s}{:s}\n", g_svCyanF, svEscaped, g_svReset);
    }

    LoadLibrary_Init();

    Systems_Init();
}

void SDK_Shutdown()
{
    Console_Shutdown();
    SpdLog_Shutdown();

    curl_global_cleanup();

    LoadLibrary_Shutdown();
    Systems_Shutdown();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            SDK_Init();
            break;
        case DLL_PROCESS_DETACH:
            SDK_Shutdown();
            break;
    };

    return TRUE;
}