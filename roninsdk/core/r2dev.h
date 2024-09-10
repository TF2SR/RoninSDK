#pragma once

#include <windows.h>

__declspec(dllexport) void DummyExport()
{
    // Required for detours.
}

// https://www.developmenttools.com/ascii-art-generator/#p=display&h=1&f=Small&t=r2sdkv0.0
const static std::string R2SDK_EMBLEM[] =
{
    R"(+---------------------------------------------------------------------+)",
    R"(|      ___         _  _          __     __                            |)",
    R"(|  _ _|_  ) ___ __| || |____ __ /  \   /  \                           |)",
    R"(| | '_|/ / (_-</ _` || / /\ V /| () |_| () |                          |)",
    R"(| |_| /___|/__/\__,_||_\_\ \_/  \__/(_)\__/                           |)",
    R"(|                                                                     |)",
    R"(+---------------------------------------------------------------------+)"
};
