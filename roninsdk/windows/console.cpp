#include "console.h"
#include <stdio.h>

#include <Windows.h>

//-----------------------------------------------------------------------------
// Purpose: sets the windows terminal background color
// Input  : color - 
//-----------------------------------------------------------------------------
void SetConsoleBackgroundColor(COLORREF color)
{
	CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx{};
	sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);

	sbInfoEx.ColorTable[0] = color;
	SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
}

void Console_Init()
{
	if (AllocConsole() == FALSE)
	{
		OutputDebugStringA("Failed to create console window!\n");
		return;
	}

	SetConsoleTitleA("Ronin Console");

	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = NULL;
	
	if (g_svCmdLine.find("-ansicolor") != string::npos)
	{
		GetConsoleMode(hOutput, &dwMode);
		dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;

		if (!SetConsoleMode(hOutput, dwMode)) // Some editions of Windows have 'VirtualTerminalLevel' disabled by default.
		{
			// Warn the user if 'VirtualTerminalLevel' could not be set on users environment.
			MessageBoxA(NULL, "Failed to set console mode 'VirtualTerminalLevel'.\n"
				"Please omit the '-ansicolor' parameter and restart \nthe program if output logging appears distorted.", "SDK Warning", MB_ICONEXCLAMATION | MB_OK);
		}

		SetConsoleBackgroundColor(0x00000000);
		AnsiColors_Init();
	}
}

void Console_Shutdown()
{
	if (FreeConsole() == FALSE)
	{
		OutputDebugStringA("Failed to destroy console window!\n");
		return;
	}
}