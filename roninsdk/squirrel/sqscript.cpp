#include "squirrel/sqscript.h"

#include "squirrel/sqvm.h"
#include "squirrel/client/sqscript.h"
#include "squirrel/server/sqscript.h"
#include "squirrel/squirrelmanager.h"
#include "squirrel/sqinit.h"
#include "speedrunning/speedometer.h"

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
		g_pSQManager<ScriptContext::CLIENT>->RegisterFunction(sqvm, "Ronin_GetPlayerPlatformVelocity",
			"Script_Ronin_GetPlayerPlatformVelocity", "Gets player platform velocity.", "vector", "entity player", &Script_Ronin_GetPlayerPlatformVelocity);
		break;
	case ScriptContext::UI:
		g_pSQManager<ScriptContext::UI>->SQVMCreated(sqvm);
		g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "GetSdkVersion", "Script_GetSdkVersion", "Returns the sdk version as a string.", "string", "", &SHARED::GetSdkVersion<ScriptContext::UI>);
		g_pSQManager<ScriptContext::UI>->RegisterFunction(sqvm, "StringToAsset", "Script_StringToAsset", "Converts a string to an asset.", "asset", "string assetName", &SHARED::StringToAsset<ScriptContext::UI>);
		// ModTimer_RegisterFuncs_UI(sqvm);
		break;
	}

	return sqvm;
}

template <ScriptContext context>
void* SQCompiler_Create(HSquirrelVM* sqvm, void* a2, void* a3, SQBool bShouldThrowError)
{
	DevMsg(eDLL_T::SCRIPT_UI, "fatal? %s %d\n", SQ_GetContextName(SQ_GetVMContext(sqvm)).c_str(), bShouldThrowError);
	// store whether the compile attempt should be fatal
	if (SQ_GetVMContext(sqvm) == ScriptContext::UI)
		g_pSQManager<ScriptContext::UI>->fatalCompileErrors = bShouldThrowError;
	else
		g_pSQManager<context>->fatalCompileErrors = bShouldThrowError;

	return v_SQCompiler_Create<context>(sqvm, a2, a3, bShouldThrowError);
}

// TODO [Fifty]: Hook VMDestroy

///////////////////////////////////////////////////////////////////////////////
// CLIENT
void VSQVM_CLIENT::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::CLIENT>, &CSquirrelVM_Init<ScriptContext::CLIENT>);
	DetourAttach((LPVOID*)&v_SQCompiler_Create<ScriptContext::CLIENT>, &SQCompiler_Create<ScriptContext::CLIENT>);
}

void VSQVM_CLIENT::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::CLIENT>, &CSquirrelVM_Init<ScriptContext::CLIENT>);
	DetourDetach((LPVOID*)&v_SQCompiler_Create<ScriptContext::CLIENT>, &SQCompiler_Create<ScriptContext::CLIENT>);
}

///////////////////////////////////////////////////////////////////////////////
// SERVER
void VSQVM_SERVER::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::SERVER>, &CSquirrelVM_Init<ScriptContext::SERVER>);
	DetourAttach((LPVOID*)&v_SQCompiler_Create<ScriptContext::SERVER>, &SQCompiler_Create<ScriptContext::SERVER>);
}

void VSQVM_SERVER::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CSquirrelVM_Init<ScriptContext::SERVER>, &CSquirrelVM_Init<ScriptContext::SERVER>);
	DetourDetach((LPVOID*)&v_SQCompiler_Create<ScriptContext::SERVER>, &SQCompiler_Create<ScriptContext::SERVER>);
}
