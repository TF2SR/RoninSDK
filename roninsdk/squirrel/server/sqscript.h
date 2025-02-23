#pragma once
// SERVER

#include "squirrel/sqscript.h"

///////////////////////////////////////////////////////////////////////////////
class VSQVM_SERVER : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CSquirrelVM_SERVER_Init", p_CSquirrelVM_Init<ScriptContext::SERVER>.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CSquirrelVM_Init<ScriptContext::SERVER> = g_pServerDll->Offset(0x260E0);
		v_CSquirrelVM_Init<ScriptContext::SERVER> = p_CSquirrelVM_Init<ScriptContext::SERVER>.RCast<CSquirrelVM*(*)(void*, ScriptContext)>();
		p_SQCompiler_Create<ScriptContext::SERVER> = g_pServerDll->Offset(0x8AA0);
		v_SQCompiler_Create<ScriptContext::SERVER> = p_SQCompiler_Create<ScriptContext::SERVER>.RCast<void* (*)(HSquirrelVM * sqvm, void* a2, void* a3, SQBool bShouldThrowError)>();
		p_DestroyVM<ScriptContext::SERVER> = g_pServerDll->Offset(0x26E20);
		v_DestroyVM<ScriptContext::SERVER> = p_DestroyVM<ScriptContext::SERVER>.RCast<void (*)(void* a1, CSquirrelVM * sqvm)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////