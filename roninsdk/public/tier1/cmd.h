//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $NoKeywords: $
//===========================================================================//

#ifndef CMD_H
#define CMD_H

//#include "tier1/utlvector.h"
//#include "tier1/utlstring.h"
//#include "tier1/characterset.h"
#include "public/iconvar.h"
#include "public/iconcommand.h"
#include "mathlib/color.h"

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class ConCommandBase;

//-----------------------------------------------------------------------------
// Any executable that wants to use ConVars need to implement one of
// these to hook up access to console variables.
//-----------------------------------------------------------------------------
class IConCommandBaseAccessor
{
public:
	// Flags is a combination of FCVAR flags in cvar.h.
	// hOut is filled in with a handle to the variable.
	virtual bool RegisterConCommandBase(ConCommandBase* pVar) = 0;
};

//-----------------------------------------------------------------------------
// Purpose: Command buffer context
//-----------------------------------------------------------------------------
enum class ECommandTarget_t : int
{
	CBUF_FIRST_PLAYER = 0,
	CBUF_LAST_PLAYER = 1, // MAX_SPLITSCREEN_CLIENTS - 1, MAX_SPLITSCREEN_CLIENTS = 2
	CBUF_SERVER = CBUF_LAST_PLAYER + 1,

	CBUF_COUNT,
};

//-----------------------------------------------------------------------------
// Sources of console commands
//-----------------------------------------------------------------------------
enum class cmd_source_t : int
{
	kCommandSrcCode,
	kCommandSrcClientCmd,
	kCommandSrcUserInput,
	kCommandSrcNetClient,
	kCommandSrcNetServer,
	kCommandSrcDemoFile,
	kCommandSrcInvalid = -1
};

//-----------------------------------------------------------------------------
// Purpose: Command tokenizer
//-----------------------------------------------------------------------------
class CCommand
{
public:
	CCommand() = delete;

	int64_t ArgC() const;
	const char** ArgV() const;
	const char* ArgS() const; // All args that occur after the 0th arg, in string form
	const char* GetCommandString() const; // The entire command in string form, including the 0th arg
	const char* operator[](int nIndex) const; // Gets at arguments
	const char* Arg(int nIndex) const; // Gets at arguments

	static int MaxCommandLength();

private:
	enum
	{
		COMMAND_MAX_ARGC = 64,
		COMMAND_MAX_LENGTH = 512,
	};

	int64_t m_nArgc;
	int64_t m_nArgv0Size;
	char m_pArgSBuffer[COMMAND_MAX_LENGTH];
	char m_pArgvBuffer[COMMAND_MAX_LENGTH];
	const char* m_ppArgv[COMMAND_MAX_ARGC];
};
//-----------------------------------------------------------------------------
// Purpose: The base console invoked command/cvar interface
//-----------------------------------------------------------------------------
class ConCommandBase
{
public:
	bool HasFlags(int nFlags);
	void AddFlags(int nFlags);
	void RemoveFlags(int nFlags);

	bool IsCommand(void) const;
	bool IsRegistered(void) const;
	bool IsFlagSet(int nFlags) const;
	static bool IsFlagSet(ConCommandBase* pCommandBase, int nFlags); // For hooking to engine's implementation.

	int GetFlags(void) const;
	ConCommandBase* GetNext(void) const;
	const char* GetHelpText(void) const;

	char* CopyString(const char* szFrom) const;

	void* m_pConCommandBaseVTable; // 0x0000
	ConCommandBase* m_pNext; // 0x0008
	bool m_bRegistered; // 0x0010
	char pad_0011[7]; // 0x0011 <- 3 bytes padding + unk int32.
	const char* m_pszName; // 0x0018
	const char* m_pszHelpString; // 0x0020
	int m_nFlags; // 0x0028
	ConCommandBase* s_pConCommandBases; // 0x002C
	IConCommandBaseAccessor* s_pAccessor; // 0x0034
}; // Size: 0x0040
static_assert(sizeof(ConCommandBase) == 0x40);

//-----------------------------------------------------------------------------
// Purpose: The console invoked command
//-----------------------------------------------------------------------------
class ConCommand : public ConCommandBase
{
	friend class CCVar;

public:
	ConCommand(void); // !TODO: Rebuild engine constructor in SDK instead.
	ConCommand(const char* szName, const char* szHelpString, int nFlags, void* pCallback, void* pCommandCompletionCallback);

	static ConCommand* StaticCreate(const char* szName, const char* szHelpString, int nFlags,
		FnCommandCallback_t pCallback, FnCommandCompletionCallback pCommandCompletionCallback);

	static void StaticInit(void);
	static void InitShipped(void);
	static void PurgeShipped(void);

	void Init(void);
	bool IsCommand(void) const;

	FnCommandCallback_t m_fnCommandCallback{}; // 0x0040 <- starts from 0x40 since we inherit ConCommandBase.
	FnCommandCompletionCallback m_fnCompletionCallback{}; // 0x0048 <- defaults to sub_180417410 ('xor eax, eax').
	int m_nCallbackFlags{}; // 0x0050
	char pad_0054[4]; // 0x0054
	int unk0; // 0x0058
	int unk1; // 0x005C
}; // Size: 0x0060

/* ==== COMMAND_BUFFER ================================================================================================================================================== */
inline CMemory p_Cbuf_AddText;
inline auto Cbuf_AddText = p_Cbuf_AddText.RCast<void (*)(ECommandTarget_t eTarget, const char* pText, cmd_source_t cmdSource)>();

/* ==== CONCOMMAND ====================================================================================================================================================== */
inline CMemory p_ConCommand_ConCommand;
inline auto v_ConCommand_ConCommand = p_ConCommand_ConCommand.RCast<void(*)(void* newCommand, const char* name, FnCommandCallback_t callback, const char* helpString, int flags, void* parent)>();

///////////////////////////////////////////////////////////////////////////////
ECommandTarget_t Cbuf_GetCurrentPlayer(void);

///////////////////////////////////////////////////////////////////////////////
class VConCommand : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("ConCommand::ConCommand", p_ConCommand_ConCommand.GetPtr());
		LogFunAdr("Cbuf_AddText", p_Cbuf_AddText.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_ConCommand_ConCommand = g_pEngineDll->Offset(0x415F60); /* "40 53 48 83 EC 20 48 8B D9 45 33 D2 4C 89 41 40" */
		v_ConCommand_ConCommand = p_ConCommand_ConCommand.RCast<void(*)(void* newCommand, const char* name, FnCommandCallback_t callback, const char* helpString, int flags, void* parent)>();
		
		p_Cbuf_AddText = g_pEngineDll->Offset(0x1203B0);
		Cbuf_AddText = p_Cbuf_AddText.RCast<void (*)(ECommandTarget_t eTarget, const char* pText, cmd_source_t cmdSource)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////

#endif // CMD_H
