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
	auto time = std::chrono::duration_cast<std::chrono::duration<int, std::micro>>(point2 - point);
	point = point2;

	g_pSQManager<ScriptContext::UI>->PushInteger(sqvm, time.count());
	return SQRESULT_NOTNULL;
}

SQRESULT Script_Timer_SetCurrentStartPoint(HSquirrelVM* sqvm)
{
	curStartPoint = g_pSQManager<ScriptContext::SERVER>->GetInteger(sqvm, 1);
	return SQRESULT_NULL;
}

SQRESULT Script_Timer_GetCurrentStartPoint(HSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::UI>->PushInteger(sqvm, curStartPoint);
	return SQRESULT_NOTNULL;
}

template <ScriptContext context>
SQRESULT Script_IsInCutscene(HSquirrelVM* sqvm)
{
	g_pSQManager<context>->PushInteger(sqvm, p_inCutscene.GetValue<bool>());
	return SQRESULT_NOTNULL;
}

SQRESULT Script_IsInLoadingScreen(HSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::UI>->PushInteger(sqvm, p_inLoadingScreen.GetValue<bool>());
	return SQRESULT_NOTNULL;
}

SQRESULT Script_GetEngineTick(HSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::UI>->PushInteger(sqvm, p_tickCount.GetValue<int>());
	return SQRESULT_NOTNULL;
}

bool shouldChangeLevel;
SQRESULT Script_SetShouldChangeLevel(HSquirrelVM* sqvm)
{
	// stub.
	shouldChangeLevel = g_pSQManager<ScriptContext::UI>->GetBool(sqvm, 1);
	return SQRESULT_NULL;
}

SQRESULT Script_HasCurrentLevelEnded(HSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::UI>->PushBool(sqvm, hasLevelEnded);
	return SQRESULT_NOTNULL;
}

SQRESULT Script_ChangeLevel(HSquirrelVM* sqvm)
{
	std::string targetLevel = g_pSQManager<ScriptContext::SERVER>->GetString(sqvm, 1);
	std::string currentLevel = v_currentMap;

	DevMsg(eDLL_T::SERVER, targetLevel.c_str());
	DevMsg(eDLL_T::SERVER, currentLevel.c_str());

	if (!shouldChangeLevel && currentLevel != targetLevel)
	{
		hasLevelEnded = true;
		return SQRESULT_NULL;
	}

	return v_Script_ChangeLevel(sqvm);
}

void ModTimer_RegisterFuncs_UI(CSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "IsInCutscene", "bool", "", &Script_IsInCutscene<ScriptContext::UI>);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "StartClockTime", "void", "", &Script_StartClockTime);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "GetCurrentClockTime", "int", "", &Script_GetCurrentClockTime);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "IsInLoadingScreen", "bool", "", &Script_IsInLoadingScreen);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "GetEngineTick", "int", "", &Script_GetEngineTick);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "SetShouldChangeLevel", "void", "bool should", &Script_SetShouldChangeLevel);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "HasCurrentLevelEnded", "bool", "", &Script_HasCurrentLevelEnded);
	g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "Timer_GetCurrentStartPoint", "int", "", &Script_Timer_GetCurrentStartPoint);
}

void ModTimer_RegisterFuncs_Client(CSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::CLIENT>->RegisterFunction(sqvm, "IsInCutscene", "bool", "", &Script_IsInCutscene<ScriptContext::CLIENT>);
}

void LoadSavedGame(CCommand& command)
{
	HSquirrelVM* sqvm = g_pSQManager<ScriptContext::UI>->m_pSQVM->sqvm;
	if (g_pSQManager<ScriptContext::UI>->PushFuncOntoStack("CodeCallback_SetLoadedSaveFile"))
	{
		g_pSQManager<ScriptContext::UI>->PushString(sqvm, command.ArgS(), -1);
		SQRESULT result = g_pSQManager<ScriptContext::UI>->Call(sqvm, 1, false, true);
	}
	v_LoadSavedGame(command);
}

void VModTimerServer::Attach(void) const
{
	DetourAttach(&v_Script_ChangeLevel, Script_ChangeLevel);
}

void VModTimerServer::Detach(void) const
{
	DetourDetach(&v_Script_ChangeLevel, Script_ChangeLevel);
}

void VModTimerEngine::Attach(void) const
{
	DetourAttach(&v_LoadSavedGame, LoadSavedGame);
}

void VModTimerEngine::Detach(void) const
{
	DetourDetach(&v_LoadSavedGame, LoadSavedGame);
}
