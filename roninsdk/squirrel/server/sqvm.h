#pragma once
// SERVER

#include "squirrel/sqvm.h"

///////////////////////////////////////////////////////////////////////////////
class HSQVM_SERVER : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("SQVM_SERVER_PrintFunc", p_SQVM_PrintFunc<ScriptContext::SERVER>.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_SQVM_PrintFunc<ScriptContext::SERVER> = g_pServerDll->Offset(0x1FE90); /* "24 20 BA 00 08 00 00 E8  E4 AC 6F 00 80 3D BC 90" - 32 */
		v_SQVM_PrintFunc<ScriptContext::SERVER> = p_SQVM_PrintFunc<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM*, SQChar*, ...)>();

		p_SQVM_CompileError<ScriptContext::SERVER> = g_pServerDll->Offset(0x799E0);
		v_SQVM_CompileError<ScriptContext::SERVER> = p_SQVM_CompileError<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM*, const SQChar*, const SQChar*, SQUnsignedInteger, SQInteger)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////