#include "squirrel/sqscript.h"

#include "squirrel/sqvm.h"
#include "squirrel/client/sqscript.h"
#include "squirrel/server/sqscript.h"
#include "squirrel/squirrelmanager.h"
#include "squirrel/sqinit.h"

template <ScriptContext context>
CSquirrelVM* CSquirrelVM_Init(void* a1, ScriptContext nSqContext)
{
	CSquirrelVM* sqvm = v_CSquirrelVM_Init<context>(a1, nSqContext);
	DevMsg((eDLL_T)context, "Created %s VM: '0x%p'\n", SQ_GetContextName(nSqContext).c_str(), sqvm);

	switch (nSqContext)
	{
	case ScriptContext::SERVER:
		g_pSQManager<ScriptContext::SERVER>->SQVMCreated(sqvm);
		g_pSQManager<ScriptContext::SERVER>->RegisterFunction(sqvm, "GetSdkVersion", "Script_GetSdkVersion", "Returns the sdk version as a string", "string", "", &SHARED::GetSdkVersion<ScriptContext::SERVER>);
		g_pSQManager<ScriptContext::SERVER>->RegisterFunction(sqvm, "StringToAsset", "Script_StringToAsset", "Converts a string to an asset.", "asset", "string assetName", &SHARED::StringToAsset<ScriptContext::SERVER>);
		break;
	case ScriptContext::CLIENT:
		g_pSQManager<ScriptContext::CLIENT>->SQVMCreated(sqvm);
		g_pSQManager<ScriptContext::CLIENT>->RegisterFunction(sqvm, "GetSdkVersion", "Script_GetSdkVersion", "Returns the sdk version as a string.", "string", "", &SHARED::GetSdkVersion<ScriptContext::CLIENT>);
		g_pSQManager<ScriptContext::CLIENT>->RegisterFunction(sqvm, "StringToAsset", "Script_StringToAsset", "Converts a string to an asset.", "asset", "string assetName", &SHARED::StringToAsset<ScriptContext::CLIENT>);
		break;
	case ScriptContext::UI:
		g_pSQManager<ScriptContext::UI>->SQVMCreated(sqvm);
		g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "GetSdkVersion", "Script_GetSdkVersion", "Returns the sdk version as a string.", "string", "", &SHARED::GetSdkVersion<ScriptContext::UI>);
		g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "StringToAsset", "Script_StringToAsset", "Converts a string to an asset.", "asset", "string assetName", &SHARED::StringToAsset<ScriptContext::UI>);
		break;
	}

	return sqvm;
}

// TODO [Fifty]: Hook VMDestroy

///////////////////////////////////////////////////////////////////////////////
// CLIENT
void VSQVM_CLIENT::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::CLIENT>, &CSquirrelVM_Init<ScriptContext::CLIENT>);
}

void VSQVM_CLIENT::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::CLIENT>, &CSquirrelVM_Init<ScriptContext::CLIENT>);
}

///////////////////////////////////////////////////////////////////////////////
// SERVER
void VSQVM_SERVER::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::SERVER>, &CSquirrelVM_Init<ScriptContext::SERVER>);
}

void VSQVM_SERVER::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::SERVER>, &CSquirrelVM_Init<ScriptContext::SERVER>);
}
