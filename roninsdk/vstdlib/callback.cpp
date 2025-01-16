//=============================================================================//
//
// Purpose: Callback functions for Concommands
//
//=============================================================================//

#include "callback.h"
#include "squirrel/squirrelmanager.h"

/*
=====================
SIG_GetAdr_f

  Logs the sigscan
  results to the console.
=====================
*/
void SIG_GetAdr_f(const CCommand& args)
{
	DetourAddress();
}

/*
=====================
SQVM_ServerScript_f

  Executes input on the
  VM in SERVER context.
=====================
*/
void SQVM_ServerScript_f(const CCommand& args)
{
	if (args.ArgC() >= 2)
	{
		g_pSQManager<ScriptContext::SERVER>->ExecuteBuffer(args.ArgS());
	}
}

/*
=====================
SQVM_ServerScript_f

  Executes buffer on the
  VM in SERVER context.
  Set the buffer through Ronin_AppendServerSquirrelBuffer in CL script
=====================
*/
void SQVM_ServerExecuteSqBuffer_f(const CCommand& args)
{
	g_pSQManager<ScriptContext::SERVER>->ExecuteBuffer(szServerSquirrelBuffer.c_str());
}

/*
=====================
SQVM_ClientScript_f

  Executes input on the
  VM in CLIENT context.
=====================
*/
void SQVM_ClientScript_f(const CCommand& args)
{
	if (args.ArgC() >= 2)
	{
		g_pSQManager<ScriptContext::CLIENT>->ExecuteBuffer(args.ArgS());
	}
}

/*
=====================
SQVM_UIScript_f

  Executes input on the
  VM in UI context.
=====================
*/
void SQVM_UIScript_f(const CCommand& args)
{
	if (args.ArgC() >= 2)
	{
		g_pSQManager<ScriptContext::UI>->ExecuteBuffer(args.ArgS());
	}
}