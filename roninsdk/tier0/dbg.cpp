//==== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. =====//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#include "core/stdafx.h"
#include "core/logdef.h"
#include "tier0/dbg.h"
#include "tier0/platform.h"
#include "tier1/cvar.h"
#ifndef NETCONSOLE
//#include "tier0/threadtools.h"
#include "tier0/commandline.h"
#ifndef DEDICATED
//#include "vgui/vgui_debugpanel.h"
//#include "gameui/IConsole.h"
#include "gameui/GameConsole.h"
#endif // !DEDICATED
#ifndef CLIENT_DLL
//#include "engine/server/sv_rcon.h"
#endif // !CLIENT_DLL

#if defined( _X360 )
#include "xbox/xbox_console.h"
#endif
//#include "squirrel/sqstdaux.h"
#endif // !NETCONSOLE
std::mutex g_LogMutex;

//-----------------------------------------------------------------------------
// True if -hushasserts was passed on command line.
//-----------------------------------------------------------------------------
bool HushAsserts()
{
#if defined (DBGFLAG_ASSERT) && !defined (NETCONSOLE)
	static bool s_bHushAsserts = !!CommandLine()->FindParm("-hushasserts");
	return s_bHushAsserts;
#else
	return true;
#endif
}

//-----------------------------------------------------------------------------
// Templates to assist in validating pointers:
//-----------------------------------------------------------------------------
/*PLATFORM_INTERFACE*/ void _AssertValidReadPtr(void* ptr, int count/* = 1*/)
{
#if defined( _WIN32 ) && !defined( _X360 )
	Assert(!IsBadReadPtr(ptr, count));
#else
	Assert(!count || ptr);
#endif
#ifdef NDEBUG
	NOTE_UNUSED(ptr);
	NOTE_UNUSED(count);
#endif // NDEBUG
}

/*PLATFORM_INTERFACE*/ void _AssertValidWritePtr(void* ptr, int count/* = 1*/)
{
#if defined( _WIN32 ) && !defined( _X360 )
	Assert(!IsBadWritePtr(ptr, count));
#else
	Assert(!count || ptr);
#endif
#ifdef NDEBUG
	NOTE_UNUSED(ptr);
	NOTE_UNUSED(count);
#endif // NDEBUG
}

/*PLATFORM_INTERFACE*/ void _AssertValidReadWritePtr(void* ptr, int count/* = 1*/)
{
#if defined( _WIN32 ) && !defined( _X360 )
	Assert(!(IsBadWritePtr(ptr, count) || IsBadReadPtr(ptr, count)));
#else
	Assert(!count || ptr);
#endif
#ifdef NDEBUG
	NOTE_UNUSED(ptr);
	NOTE_UNUSED(count);
#endif // NDEBUG
}

/*PLATFORM_INTERFACE*/ void _AssertValidStringPtr(const TCHAR* ptr, int maxchar/* = 0xFFFFFF */)
{
#if defined( _WIN32 ) && !defined( _X360 )
#ifdef TCHAR_IS_CHAR
	Assert(!IsBadStringPtr(ptr, maxchar));
#else
	Assert(ptr);
#endif
#else
	Assert(ptr);
#endif
#ifdef NDEBUG
	NOTE_UNUSED(ptr);
	NOTE_UNUSED(maxchar);
#endif // NDEBUG
}

/*PLATFORM_INTERFACE*/ void AssertValidWStringPtr(const wchar_t* ptr, int maxchar/* = 0xFFFFFF */)
{
#if defined( _WIN32 ) && !defined( _X360 )
	Assert(!IsBadStringPtrW(ptr, maxchar));
#else
	Assert(ptr);
#endif
#ifdef NDEBUG
	NOTE_UNUSED(ptr);
	NOTE_UNUSED(maxchar);
#endif // NDEBUG
}

#if !defined (DEDICATED) && !defined (NETCONSOLE)
Color CheckForWarnings(LogType_t type, eDLL_T context, const Color& defaultCol)
{
	Color color = defaultCol;
	if (type == LogType_t::LOG_WARNING)
	{
		color = Color(255, 255,   0, 210);
	}
	else if (type == LogType_t::LOG_ERROR)
	{
		color = Color(255,   0,   0, 210);
	}

	return color;
}

Color GetColorForContext(eDLL_T context)
{
	switch (context)
	{
	case eDLL_T::SCRIPT_SERVER:
		return Color(150, 150, 190, 255);
	case eDLL_T::SCRIPT_CLIENT:
		return Color(150, 150, 120, 255);
	case eDLL_T::SCRIPT_UI:
		return Color(150, 110, 120, 255);
	case eDLL_T::SERVER:
		return Color( 60, 110, 220, 255);
	case eDLL_T::CLIENT:
		return Color(110, 110, 110, 255);
	case eDLL_T::UI:
		return Color(150,  90, 110, 255);
	case eDLL_T::ENGINE:
		return Color(190, 190, 190, 255);
	case eDLL_T::FS:
		return Color( 90, 180, 190, 255);
	case eDLL_T::RTECH:
		return Color( 90, 190,  90, 255);
	case eDLL_T::MS:
		return Color(190,  76, 173, 255);
	case eDLL_T::AUDIO:
		return Color(240, 110,  30, 255);
	case eDLL_T::VIDEO:
		return Color(190,   0, 240, 255);
	case eDLL_T::RONIN_GEN:
		return Color(  0, 255, 150, 255);
	default:
		return Color(210, 210, 210, 255);
	}
}
#endif // !DEDICATED && !NETCONSOLE

const char* GetContextNameByIndex(eDLL_T context)
{
	int index = static_cast<int>(context);
	const char* contextName = "";

	switch (context)
	{
	case eDLL_T::SCRIPT_SERVER:
		contextName = "[SCRIPT SV] ";
		break;
	case eDLL_T::SCRIPT_CLIENT:
		contextName = "[SCRIPT CL] ";
		break;
	case eDLL_T::SCRIPT_UI:
		contextName = "[SCRIPT UI] ";
		break;
	case eDLL_T::SERVER:
		contextName = "[NATIVE SV] ";
		break;
	case eDLL_T::CLIENT:
		contextName = "[NATIVE CL] ";
		break;
	case eDLL_T::UI:
		contextName = "[NATIVE UI] ";
		break;
	case eDLL_T::ENGINE:
		contextName = "[NATIVE EN] ";
		break;
	case eDLL_T::FS:
		contextName = "[FILESYSTM] ";
		break;
	case eDLL_T::RTECH:
		contextName = "[RSPN TECH] ";
		break;
	case eDLL_T::MS:
		contextName = "[MAT SYSTM] ";
		break;
	case eDLL_T::AUDIO:
		contextName = "[AUDIO SYS] ";
		break;
	case eDLL_T::VIDEO:
		contextName = "[VIDEO SYS] ";
		break;
	case eDLL_T::RONIN_GEN:
		contextName = "[RONIN GEN] ";
		break;
	default:
		break;
	}

	return contextName;
}

bool LoggedFromClient(eDLL_T context)
{
#ifndef DEDICATED
	return (context == eDLL_T::CLIENT || context == eDLL_T::SCRIPT_CLIENT
		|| context == eDLL_T::UI || context == eDLL_T::SCRIPT_UI
		|| context == eDLL_T::NETCON);
#else
	NOTE_UNUSED(context);
	return false;
#endif // !DEDICATED
}

//-----------------------------------------------------------------------------
// Purpose: Show logs to all console interfaces (va_list version)
// Input  : logType - 
//			logLevel - 
//			context - 
//			*pszLogger - 
//			*pszFormat -
//			args - 
//			exitCode - 
//			*pszUptimeOverride - 
//-----------------------------------------------------------------------------
void CoreMsgV(LogType_t logType, LogLevel_t logLevel, eDLL_T context,
	const char* pszLogger, const char* pszFormat, va_list args,
	const UINT exitCode)
{
	const bool bToConsole = (logLevel >= LogLevel_t::LEVEL_CONSOLE);
	const bool bUseColor = (bToConsole && g_bSpdLog_UseAnsiClr);

	const char* pszUpTime = context == eDLL_T::NONE ? "" : Plat_GetProcessUpTime();
	string message = g_bSpdLog_PostInit ? pszUpTime : "";

#if !defined (DEDICATED) && !defined (NETCONSOLE)
	Color contextColor = GetColorForContext(context);
	message.append(contextColor.ToANSIColor());
#endif // !DEDICATED && !NETCONSOLE

	const char* pszContext = GetContextNameByIndex(context);
	message.append(pszContext);

	bool bSquirrel = false;
	bool bWarning = false;
	bool bError = false;

	//-------------------------------------------------------------------------
	// Setup logger and context
	//-------------------------------------------------------------------------
	Color logColor = Color(210, 210, 210, 255);
	switch (logType)
	{
	case LogType_t::LOG_WARNING:
		logColor = Color(255, 255, 0, 255);
		break;
	case LogType_t::LOG_ERROR:
		logColor = Color(255, 0, 0, 255);
		break;
	case LogType_t::SQ_INFO:
		bSquirrel = true;
		break;
	case LogType_t::SQ_WARNING:
		bSquirrel = true;
		bWarning = true;
		break;
	default:
		break;
	}
	message.append(logColor.ToANSIColor());

	//-------------------------------------------------------------------------
	// Format actual input
	//-------------------------------------------------------------------------
	va_list argsCopy;
	va_copy(argsCopy, args);
	string formatted = FormatV(pszFormat, argsCopy);
	if (formatted[formatted.length() - 1] == '\n')
		formatted = formatted.substr(0, formatted.length() - 1);
	va_end(argsCopy);

	message.append(formatted);

	//-------------------------------------------------------------------------
	// Emit to all interfaces
	//-------------------------------------------------------------------------
	std::lock_guard<std::mutex> lock(g_LogMutex);
	if (bToConsole)
	{
		g_TermLogger->debug(message);

		if (bUseColor)
		{
			// Remove ANSI rows before emitting to file or over wire.
			message = std::regex_replace(message, s_AnsiRowRegex, "");
		}
	}

#ifndef NETCONSOLE

	// Output is always logged to the file.
	std::shared_ptr<spdlog::logger> ntlogger = spdlog::get("log"); // <-- Obtain by 'pszLogger'.
	assert(ntlogger.get() != nullptr);
	ntlogger->debug(message);

	if (bToConsole)
	{
#ifndef DEDICATED
		g_GameLogger->debug(message);

		if (g_bSpdLog_PostInit && g_bLogToGameConsole)
		{
			g_pCVar->ConsoleColorPrintf(Color(210, 210, 210, 255).ToSourceColor(), "%s", pszUpTime);
			g_pCVar->ConsoleColorPrintf(contextColor.ToSourceColor(), "%s", pszContext);
			g_pCVar->ConsoleColorPrintf(logColor.ToSourceColor(), "%s\n", formatted.c_str());
		}
#endif // !DEDICATED
	}	

#ifndef DEDICATED
	g_LogStream.str(string());
	g_LogStream.clear();
#endif // !DEDICATED

#endif // !NETCONSOLE

	if (exitCode) // Terminate the process if an exit code was passed.
	{
		if (MessageBoxA(NULL, Format("%s- %s", pszUpTime, message.c_str()).c_str(),
			"SDK Error", MB_ICONERROR | MB_OK))
		{
			TerminateProcess(GetCurrentProcess(), exitCode);
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Show logs to all console interfaces
// Input  : logType - 
//			logLevel - 
//			context - 
//			exitCode - 
//			*pszLogger - 
//			*pszFormat -
//			... - 
//-----------------------------------------------------------------------------
void CoreMsg(LogType_t logType, LogLevel_t logLevel, eDLL_T context,
	const UINT exitCode, const char* pszLogger, const char* pszFormat, ...)
{
	va_list args;
	va_start(args, pszFormat);
	CoreMsgV(logType, logLevel, context, pszLogger, pszFormat, args, exitCode);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Prints general debugging messages
// Input  : context - 
//			*fmt - ... - 
//-----------------------------------------------------------------------------
void DevMsg(eDLL_T context, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	CoreMsgV(LogType_t::LOG_INFO, LogLevel_t::LEVEL_NOTIFY, context, "sdk", fmt, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Prints logs from remote console
// Input  : context - 
//			*fmt - ... - 
//-----------------------------------------------------------------------------
#ifndef DEDICATED
void NetMsg(LogType_t logType, eDLL_T context, const char* uptime, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	CoreMsgV(logType, LogLevel_t::LEVEL_NOTIFY, context, "netconsole", fmt, args, NO_ERROR);
	va_end(args);
}
#endif // !DEDICATED

//-----------------------------------------------------------------------------
// Purpose: Print engine and SDK warnings
// Input  : context - 
//			*fmt - ... - 
//-----------------------------------------------------------------------------
void Warning(eDLL_T context, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	CoreMsgV(LogType_t::LOG_WARNING, LogLevel_t::LEVEL_NOTIFY, context, "sdk(warning)", fmt, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print engine and SDK errors
// Input  : context - 
//			code - 
//			*fmt - ... - 
//-----------------------------------------------------------------------------
void Error(eDLL_T context, const UINT code, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	CoreMsgV(LogType_t::LOG_ERROR, LogLevel_t::LEVEL_NOTIFY, context, "sdk(error)", fmt, args, code);
	va_end(args);
}