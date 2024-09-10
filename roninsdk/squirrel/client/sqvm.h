#pragma once
// CLIENT

#include "squirrel/sqvm.h"

///////////////////////////////////////////////////////////////////////////////
class HSQVM_CLIENT : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("SQVM_CLIENT_PrintFunc", p_SQVM_PrintFunc<ScriptContext::CLIENT>.GetPtr());
		LogFunAdr("SQVM_CLIENT_CompileError", p_SQVM_CompileError<ScriptContext::CLIENT>.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_SQVM_PrintFunc<ScriptContext::CLIENT> = g_pClientDll->Offset(0x12B00); /* "24 20 BA 00 08 00 00 E8  B4 0E 72 00 80 3D 6C EF" - 32 */
		v_SQVM_PrintFunc<ScriptContext::CLIENT> = p_SQVM_PrintFunc<ScriptContext::CLIENT>.RCast<SQRESULT(*)(HSquirrelVM*, SQChar*, ...)>();

		p_SQVM_CompileError<ScriptContext::CLIENT> = g_pClientDll->Offset(0x79A50);
		v_SQVM_CompileError<ScriptContext::CLIENT> = p_SQVM_CompileError<ScriptContext::CLIENT>.RCast<void(*)(HSquirrelVM*, const SQChar*, const SQChar*, SQUnsignedInteger, SQInteger)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////