#include "utility/memaddr.h"
#include "speedometer.h"
#include "mathlib/vector.h"

SQRESULT Script_Ronin_GetPlayerPlatformVelocity(HSquirrelVM* sqvm)
{
	CMemory player = CMemory(g_pSQManager<ScriptContext::CLIENT>->GetEntity<void>(sqvm, 1));
	uintptr_t thing = player.Offset(0x380).GetPtr();
	g_pSQManager<ScriptContext::CLIENT>->PushVector(sqvm, (const SQFloat*)thing);
	return SQRESULT_NOTNULL;
}