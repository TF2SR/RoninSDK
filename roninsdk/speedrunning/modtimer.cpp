#include "modtimer.h"

std::chrono::system_clock::time_point point;

SQRESULT Script_StartClockTime(HSquirrelVM* sqvm)
{
	point = std::chrono::system_clock::now();
	return SQRESULT_NULL;
}

SQRESULT Script_GetCurrentClockTime(HSquirrelVM* sqvm)
{
	std::chrono::time_point point2 = std::chrono::system_clock::now();
	std::chrono::nanoseconds time = point2 - point;
	point = point2;

	g_pSQManager<ScriptContext::UI>->PushInteger(sqvm, time.count());
	return SQRESULT_NOTNULL;
}

void ModTimer_RegisterFuncs_UI(CSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "StartClockTime", "Script_StartClockTime", "", "void", "", &Script_StartClockTime);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "GetCurrentClockTime", "Script_GetCurrentClockTime", "", "int", "", &Script_GetCurrentClockTime);
}

void VModTimerServer::Attach(void) const
{

}

