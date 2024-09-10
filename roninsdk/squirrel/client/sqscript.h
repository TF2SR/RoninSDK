#pragma once
// CLIENT

#include "squirrel/sqscript.h"

///////////////////////////////////////////////////////////////////////////////
class VSQVM_CLIENT : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CSquirrelVM_CLIENT_Init", p_CSquirrelVM_Init<ScriptContext::CLIENT>.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CSquirrelVM_Init<ScriptContext::CLIENT> = g_pClientDll->Offset(0x26130);
		v_CSquirrelVM_Init<ScriptContext::CLIENT> = p_CSquirrelVM_Init<ScriptContext::CLIENT>.RCast<CSquirrelVM*(*)(void*, ScriptContext)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////