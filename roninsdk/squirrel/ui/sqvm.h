#pragma once
// UI

#include "squirrel/sqvm.h"

///////////////////////////////////////////////////////////////////////////////
class HSQVM_UI : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("SQVM_UI_PrintFunc", p_SQVM_PrintFunc<ScriptContext::UI>.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_SQVM_PrintFunc<ScriptContext::UI> = g_pClientDll->Offset(0x12BA0); /* "24 20 BA 00 08 00 00 E8  14 0E 72 00 80 3D CC EE" - 32 */
		v_SQVM_PrintFunc<ScriptContext::UI> = p_SQVM_PrintFunc<ScriptContext::UI>.RCast<SQRESULT(*)(HSquirrelVM*, SQChar*, ...)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////