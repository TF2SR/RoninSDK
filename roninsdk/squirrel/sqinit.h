#pragma once

#include "squirrel/sqclasstypes.h"
#include "squirrel/squirrelmanager.h"
#include "speedrunning/roninversion.h"
#include "speedrunning/updatechecker.h"


namespace SHARED
{
	//-----------------------------------------------------------------------------
	// Purpose: Returns SDK Version as a string
	//-----------------------------------------------------------------------------
	template<ScriptContext context>
	SQRESULT GetSdkVersion(HSquirrelVM* sqvm)
	{
		g_pSQManager<context>->PushString(sqvm, RONIN_VERSION, strlen(RONIN_VERSION));
		return SQRESULT_NOTNULL;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Returns passed string as an asset
	//-----------------------------------------------------------------------------
	template<ScriptContext context>
	SQRESULT StringToAsset(HSquirrelVM* sqvm)
	{
		g_pSQManager<context>->PushAsset(sqvm, g_pSQManager<context>->GetString(sqvm, 1), -1);
		return SQRESULT_NOTNULL;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Prints the location of an entity in memory
	//-----------------------------------------------------------------------------
	template<ScriptContext context>
	SQRESULT PrintEntityAddress(HSquirrelVM* sqvm)
	{
		CMemory player = CMemory(g_pSQManager<context>->GetEntity<void>(sqvm, 1));

		DevMsg(eDLL_T::RONIN_GEN, "%p", g_pSQManager<context>->GetEntity<void>(sqvm, 1));
		return SQRESULT_NOTNULL;
	}
}
namespace SERVER
{
}
namespace CLIENT
{
}
namespace UI
{
	inline SQRESULT CheckForUpdates(HSquirrelVM* sqvm)
	{
		UpdateChecker_Start();
		return SQRESULT_NULL;
	}

	inline SQRESULT GetUpdateState(HSquirrelVM* sqvm)
	{
		const char* state = UpdateChecker_Poll();
		g_pSQManager<ScriptContext::UI>->PushString(sqvm, state, -1);
		return SQRESULT_NOTNULL;
	}

	inline SQRESULT GetLatestVersion(HSquirrelVM* sqvm)
	{
		const auto& version = UpdateChecker_LatestVersion();
		g_pSQManager<ScriptContext::UI>->PushString(sqvm, version.c_str(), -1);
		return SQRESULT_NOTNULL;
	}
}
