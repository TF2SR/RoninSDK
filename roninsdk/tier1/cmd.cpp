//=============================================================================//
//
// Purpose: Console Commands
//
//=============================================================================//

#include "core/stdafx.h"
//#include "tier0/tslist.h"
#include "tier0/memstd.h"
#include "tier0/commandline.h"
#include "tier1/cmd.h"
#include "tier1/cvar.h"
//#include "tier1/characterset.h"
//#include "tier1/utlstring.h"
//#include "vstdlib/completion.h"
#include "vstdlib/callback.h"
#include "engine/console.h"


//-----------------------------------------------------------------------------
// Tokenizer class
//-----------------------------------------------------------------------------
int CCommand::MaxCommandLength()
{
	return COMMAND_MAX_LENGTH - 1;
}
int64_t CCommand::ArgC() const
{
	return m_nArgc;
}
const char** CCommand::ArgV() const
{
	return m_nArgc ? (const char**)m_ppArgv : NULL;
}
const char* CCommand::ArgS() const
{
	return m_nArgv0Size ? &m_pArgSBuffer[m_nArgv0Size] : "";
}
const char* CCommand::GetCommandString() const
{
	return m_nArgc ? m_pArgSBuffer : "";
}
const char* CCommand::Arg(int nIndex) const
{
	// FIXME: Many command handlers appear to not be particularly careful
	// about checking for valid argc range. For now, we're going to
	// do the extra check and return an empty string if it's out of range
	if (nIndex < 0 || nIndex >= m_nArgc)
		return "";
	return m_ppArgv[nIndex];
}
const char* CCommand::operator[](int nIndex) const
{
	return Arg(nIndex);
}

//-----------------------------------------------------------------------------
// Purpose: create
//-----------------------------------------------------------------------------

ConCommand* ConCommand::StaticCreate(const char* pszName, const char* pszHelpString, int nFlags,
	FnCommandCallback_t pCallback, FnCommandCompletionCallback pCompletionFunc)
{
	ConCommand* pCommand = MemAllocSingleton()->Alloc<ConCommand>(sizeof(ConCommand));

	v_ConCommand_ConCommand(pCommand, pszName, pCallback, pszHelpString, nFlags, nullptr);
	
	return pCommand;
}

//-----------------------------------------------------------------------------
// Purpose: construct/allocate
//-----------------------------------------------------------------------------
ConCommand::ConCommand()
	: m_fnCompletionCallback(nullptr),
	pad_0054(),
	unk0(0),
	unk1(0)
{
}
//-----------------------------------------------------------------------------
// Purpose: ConCommand registration
//-----------------------------------------------------------------------------

void ConCommand::StaticInit(void)
{
	//-------------------------------------------------------------------------
	// ENGINE DLL                                                             |

	//-------------------------------------------------------------------------
	// TIER0                                                                  |
	ConCommand::StaticCreate("sig_getadr", "Logs the sigscan results to the console.", FCVAR_DONTRECORD/*FCVAR_DEVELOPMENTONLY | FCVAR_HIDDEN*/, SIG_GetAdr_f, nullptr);

	//-------------------------------------------------------------------------
	// SERVER DLL                                                             |
	ConCommand::StaticCreate("script", "Run input code as SERVER script on the VM.", FCVAR_GAMEDLL | FCVAR_GAMEDLL_FOR_REMOTE_CLIENTS | FCVAR_CHEAT, SQVM_ServerScript_f, nullptr);
	ConCommand::StaticCreate("script_executesqbuffer", "Run code in buffer as SERVER script on the VM.", FCVAR_GAMEDLL | FCVAR_GAMEDLL_FOR_REMOTE_CLIENTS, SQVM_ServerExecuteSqBuffer_f, nullptr);

	//-------------------------------------------------------------------------
	// CLIENT DLL                                                             |
	ConCommand::StaticCreate("script_client", "Run input code as CLIENT script on the VM.", FCVAR_CLIENTDLL | FCVAR_CHEAT, SQVM_ClientScript_f, nullptr);

	ConCommand::StaticCreate("toggleconsole", "Show/hide the console.", FCVAR_DONTRECORD, Con_ToggleConsole_f, nullptr);
	ConCommand::StaticCreate("hideconsole", "Hide the console.", FCVAR_DONTRECORD, Con_HideConsole_f, nullptr);
	ConCommand::StaticCreate("showconsole", "Show the console.", FCVAR_DONTRECORD, Con_ShowConsole_f, nullptr);
	//-------------------------------------------------------------------------
	// UI DLL                                                                 |
	ConCommand::StaticCreate("script_ui", "Run input code as UI script on the VM.", FCVAR_CLIENTDLL, SQVM_UIScript_f, nullptr);
}

//-----------------------------------------------------------------------------
// Purpose: shipped ConCommand initialization
//-----------------------------------------------------------------------------

void ConCommand::InitShipped(void)
{
	/*
	///------------------------------------------------------ [ CALLBACK SWAP ]
	//-------------------------------------------------------------------------
	// ENGINE DLL                                                             |
	ConCommand* changelevel = g_pCVar->FindCommand("changelevel");
	ConCommand* map = g_pCVar->FindCommand("map");
	ConCommand* map_background = g_pCVar->FindCommand("map_background");
	ConCommand* ss_map = g_pCVar->FindCommand("ss_map");
	ConCommand* migrateme = g_pCVar->FindCommand("migrateme");
	ConCommand* help = g_pCVar->FindCommand("help");
	ConCommand* convar_list = g_pCVar->FindCommand("convar_list");
	ConCommand* convar_differences = g_pCVar->FindCommand("convar_differences");
	ConCommand* convar_findByFlags = g_pCVar->FindCommand("convar_findByFlags");
#ifndef DEDICATED
	//-------------------------------------------------------------------------
	// MATERIAL SYSTEM
	ConCommand* mat_crosshair = g_pCVar->FindCommand("mat_crosshair"); // Patch callback function to working callback.
	//-------------------------------------------------------------------------
	// CLIENT DLL                                                             |
	ConCommand* give = g_pCVar->FindCommand("give");
#endif // !DEDICATED

	help->m_fnCommandCallback = CVHelp_f;
	convar_list->m_fnCommandCallback = CVList_f;
	convar_differences->m_fnCommandCallback = CVDiff_f;
	convar_findByFlags->m_fnCommandCallback = CVFlag_f;
#ifndef CLIENT_DLL
	changelevel->m_fnCommandCallback = Host_Changelevel_f;
#endif // !CLIENT_DLL
	changelevel->m_fnCompletionCallback = Host_Changelevel_f_CompletionFunc;

	map->m_fnCompletionCallback = Host_Map_f_CompletionFunc;
	map_background->m_fnCompletionCallback = Host_Background_f_CompletionFunc;
	ss_map->m_fnCompletionCallback = Host_SSMap_f_CompletionFunc;

#ifndef DEDICATED
	mat_crosshair->m_fnCommandCallback = Mat_CrossHair_f;
	give->m_fnCompletionCallback = Game_Give_f_CompletionFunc;
#endif // !DEDICATED

	/// ------------------------------------------------------ [ FLAG REMOVAL ]
	//-------------------------------------------------------------------------
	if (!CommandLine()->CheckParm("-devsdk"))
	{
		const char* pszMaskedBases[] =
		{
#ifndef DEDICATED
			"connect",
			"connectAsSpectator",
			"connectWithKey",
			"silentconnect",
			"set",
			"ping",
#endif // !DEDICATED
			"launchplaylist",
			"quit",
			"exit",
			"reload",
			"restart",
			"status",
			"version",
		};

		for (size_t i = 0; i < SDK_ARRAYSIZE(pszMaskedBases); i++)
		{
			if (ConCommandBase* pCommandBase = g_pCVar->FindCommandBase(pszMaskedBases[i]))
			{
				pCommandBase->RemoveFlags(FCVAR_DEVELOPMENTONLY);
			}
		}

		convar_list->RemoveFlags(FCVAR_DEVELOPMENTONLY);
		convar_differences->RemoveFlags(FCVAR_DEVELOPMENTONLY);
		convar_findByFlags->RemoveFlags(FCVAR_DEVELOPMENTONLY);
		help->RemoveFlags(FCVAR_DEVELOPMENTONLY);
		migrateme->RemoveFlags(FCVAR_SERVER_CAN_EXECUTE);
		changelevel->RemoveFlags(FCVAR_DEVELOPMENTONLY);
		map->RemoveFlags(FCVAR_DEVELOPMENTONLY | FCVAR_SERVER_CAN_EXECUTE);
		map_background->RemoveFlags(FCVAR_DEVELOPMENTONLY | FCVAR_SERVER_CAN_EXECUTE);
		ss_map->RemoveFlags(FCVAR_DEVELOPMENTONLY | FCVAR_SERVER_CAN_EXECUTE);
	}*/
}

//-----------------------------------------------------------------------------
// Purpose: unregister extraneous ConCommand's.
//-----------------------------------------------------------------------------

void ConCommand::PurgeShipped(void)
{
	/*
#ifdef DEDICATED
	const char* pszCommandToRemove[] =
	{
		"bind",
		"bind_held",
		"bind_list",
		"bind_list_abilities",
		"bind_US_standard",
		"bind_held_US_standard",
		"unbind",
		"unbind_US_standard",
		"unbindall",
		"unbind_all_gamepad",
		"unbindall_ignoreGamepad",
		"unbind_batch",
		"unbind_held",
		"unbind_held_US_standard",
		"uiscript_reset",
		"getpos_bind",
		"connect",
		"silent_connect",
		"ping",
		"gameui_activate",
		"gameui_hide",
		"weaponSelectOrdnance",
		"weaponSelectPrimary0",
		"weaponSelectPrimary1",
		"weaponSelectPrimary2",
		"+scriptCommand1",
		"-scriptCommand1",
		"+scriptCommand2",
		"-scriptCommand2",
		"+scriptCommand3",
		"-scriptCommand3",
		"+scriptCommand4",
		"-scriptCommand4",
		"+scriptCommand5",
		"-scriptCommand5",
		"+scriptCommand6",
		"-scriptCommand6",
		"+scriptCommand7",
		"-scriptCommand7",
		"+scriptCommand8",
		"-scriptCommand8",
		"+scriptCommand9",
		"-scriptCommand9",
	};

	for (size_t i = 0; i < SDK_ARRAYSIZE(pszCommandToRemove); i++)
	{
		ConCommandBase* pCommandBase = g_pCVar->FindCommandBase(pszCommandToRemove[i]);

		if (pCommandBase)
		{
			g_pCVar->UnregisterConCommand(pCommandBase);
		}
	}
#endif // DEDICATED
	*/
}

//-----------------------------------------------------------------------------
// Purpose: Checks if ConCommand has requested flags.
// Input  : nFlags - 
// Output : True if ConCommand has nFlags.
//-----------------------------------------------------------------------------
/*
bool ConCommandBase::HasFlags(int nFlags) const
{
	return m_nFlags & nFlags;
}*/

//-----------------------------------------------------------------------------
// Purpose: 
// Output : const ConCommandBase
//-----------------------------------------------------------------------------
ConCommandBase* ConCommandBase::GetNext(void) const
{
	return m_pNext;
}

//-----------------------------------------------------------------------------
// Purpose: Copies string using local new/delete operators
// Input  : *szFrom - 
// Output : char
//-----------------------------------------------------------------------------
char* ConCommandBase::CopyString(const char* szFrom) const
{
	size_t nLen;
	char* szTo;

	nLen = strlen(szFrom);
	if (nLen <= 0)
	{
		szTo = new char[1];
		szTo[0] = 0;
	}
	else
	{
		szTo = new char[nLen + 1];
		memmove(szTo, szFrom, nLen + 1);
	}
	return szTo;
}

//-----------------------------------------------------------------------------
// Purpose: Returns current player calling this function
// Output : ECommandTarget_t - 
//-----------------------------------------------------------------------------
ECommandTarget_t Cbuf_GetCurrentPlayer(void)
{
	// Always returns 'CBUF_FIRST_PLAYER' in Respawn's code.
	return ECommandTarget_t::CBUF_FIRST_PLAYER;
}

///////////////////////////////////////////////////////////////////////////////
void VConCommand::Attach() const
{
	//DetourAttach((LPVOID*)&v_ConCommand_ConCommand, &Cmd_ForwardToServer);
}
void VConCommand::Detach() const
{
	//DetourDetach((LPVOID*)&v_ConCommand_ConCommand, &Cmd_ForwardToServer);
}
