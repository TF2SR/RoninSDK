#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <shlwapi.h>

#define ARRAY_LEN(arr) sizeof(arr) / sizeof(arr[0])

static const WCHAR* DLL_PATHS[] = {
    L"%ls\\roninsdk.dll",
    L"%ls\\..\\roninsdk.dll",
};

bool GetModPathW(HMODULE module, wchar_t* dest, DWORD destSize)
{
    if (!dest)
        return NULL;
    if (destSize < MAX_PATH)
        return NULL;

    DWORD length = GetModuleFileNameW(module, dest, destSize);
    return length && PathRemoveFileSpecW(dest);
}

void Error(std::string szErrorMessage)
{
    MessageBoxA(
        GetForegroundWindow(),
        szErrorMessage.c_str(),
        "Shim error",
        0
    );
}

extern "C" __declspec(dllexport) bool InitialiseNorthstar()
{
    WCHAR szExePath[MAX_PATH];
    WCHAR buffer[MAX_PATH*2];
    HMODULE current_module = NULL;
    HMODULE dll = NULL;

    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCWSTR)&InitialiseNorthstar, &current_module) == 0)
    {
        Error("Failed to get module handle!");
        return false;
    }

    if (!GetModPathW(current_module, szExePath, sizeof(szExePath)))
    {
        Error("Failed to get module filename!");
        return false;
    }

    for (size_t i = 0; i < ARRAY_LEN(DLL_PATHS); ++i)
    {
        swprintf_s(buffer, ARRAY_LEN(buffer), DLL_PATHS[i], szExePath);
        dll = LoadLibraryExW(buffer, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (!dll)
            continue;

        break;
    }

    // Ronin couldn't be found
    if (!dll)
        return false;

    // RoninSDK initializes via DllMain so no extra logic is needed
    return true;
}

