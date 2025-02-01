#include "utility/memaddr.h"
#include "speedometer.h"
#include "mathlib/vector.h"
#include "vstdlib/callback.h"

SQRESULT Script_Ronin_GetPlayerPlatformVelocity(HSquirrelVM* sqvm)
{
	CMemory player = CMemory(g_pSQManager<ScriptContext::CLIENT>->GetEntity<void>(sqvm, 1));
	CMemory platVelocityVector = player.Offset(0x380);

	// fixes platformvelocity being wrong when having 1024hu/s of platformvel in an axis
	if (svPlayer && (fabs(player.Offset(0x380).GetValue<float>()) >= 1023 || fabs(player.Offset(0x384).GetValue<float>()) >= 1023))
	{
		platVelocityVector = svPlayer.Offset(0x41C).GetPtr();
	}
	g_pSQManager<ScriptContext::CLIENT>->PushVector(sqvm, (const SQFloat*)platVelocityVector.GetPtr());
	return SQRESULT_NOTNULL;
}

SQRESULT Script_Ronin_SetServerPlayer(HSquirrelVM* sqvm)
{
	svPlayer = CMemory(g_pSQManager<ScriptContext::SERVER>->GetEntity<void>(sqvm, 1));
	return SQRESULT_NULL;
}

SQRESULT Script_Ronin_AppendServerSquirrelBuffer(HSquirrelVM* sqvm)
{
	DevMsg(eDLL_T::SCRIPT_CLIENT, "appending stuff");
	std::string file = g_pSQManager<ScriptContext::CLIENT>->GetString(sqvm, 1);
	file = "./ronin/scripts/vscripts/" + file;
	DevMsg(eDLL_T::SCRIPT_CLIENT, file.c_str());
	std::ifstream fileStr(file);
	if (fileStr.fail())
	{
		spdlog::error("A file was supposed to be loaded but we can't access it?!");
		g_pSQManager<ScriptContext::CLIENT>->RaiseError(sqvm, "A file was supposed to be loaded but we can't access it?!");
		return SQRESULT_ERROR;
	}

	std::stringstream stringStream;
	stringStream << fileStr.rdbuf();

	szServerSquirrelBuffer += stringStream.str() + "\n";
	return SQRESULT_NOTNULL;
}