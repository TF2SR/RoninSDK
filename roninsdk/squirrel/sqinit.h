#pragma once

#include "squirrel/sqclasstypes.h"


namespace SHARED
{
	//-----------------------------------------------------------------------------
	// Purpose: Returns SDK Version as a string
	//-----------------------------------------------------------------------------
	template<ScriptContext context>
	SQRESULT GetSdkVersion(HSquirrelVM* sqvm)
	{
		g_pSQManager<context>->PushString(sqvm, "0.0", 4);
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
		g_pSQManager<context>->PushAsset(sqvm, g_pSQManager<context>->GetString(sqvm, 1), -1);
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
}