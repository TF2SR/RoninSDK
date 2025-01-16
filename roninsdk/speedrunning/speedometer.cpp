#include "utility/memaddr.h"
#include "speedometer.h"
#include "mathlib/vector.h"
#include "vstdlib/callback.h"

SQRESULT Script_Ronin_GetPlayerPlatformVelocity(HSquirrelVM* sqvm)
{
	CMemory player = CMemory(g_pSQManager<ScriptContext::CLIENT>->GetEntity<void>(sqvm, 1));
	uintptr_t platVelocityVector = player.Offset(0x380).GetPtr();
	g_pSQManager<ScriptContext::CLIENT>->PushVector(sqvm, (const SQFloat*)platVelocityVector);
	return SQRESULT_NOTNULL;
}

SQRESULT Script_Ronin_AppendServerSquirrelBuffer(HSquirrelVM* sqvm)
{
	DevMsg(eDLL_T::SCRIPT_CLIENT, "appending stuff");
	std::string buf = g_pSQManager<ScriptContext::CLIENT>->GetString(sqvm, 1);
	DevMsg(eDLL_T::SCRIPT_CLIENT, buf.c_str());
	szServerSquirrelBuffer += buf;
	return SQRESULT_NOTNULL;
}