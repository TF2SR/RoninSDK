#include "squirrel/sqclasstypes.h"
#include "squirrel/sqdatatypes.h"
#include "squirrel/squirrelmanager.h"
#include "iconvar.h"
#include "tier1/cmd.h"

SQRESULT Script_Timer_SetCurrentStartPoint(HSquirrelVM* sqvm);
void ModTimer_RegisterFuncs_Client(CSquirrelVM* sqvm);
void ModTimer_RegisterFuncs_UI(CSquirrelVM* sqvm);

inline bool hasLevelEnded;
inline int curStartPoint = -1;

inline CMemory p_inLoadingScreen;
inline CMemory p_tickCount;
inline CMemory p_inCutscene;

inline CMemory p_currentMap;
inline auto v_currentMap = p_currentMap.RCast<const char*>();

inline CMemory p_Script_ChangeLevel;
inline auto v_Script_ChangeLevel = p_Script_ChangeLevel.RCast<SQRESULT(*)(HSquirrelVM* sqvm)>();

inline CMemory p_LoadSavedGame;
inline auto v_LoadSavedGame = p_LoadSavedGame.RCast<void(*)(CCommand & sqvm)>();

inline CMemory p_ChangeLevel;
inline auto v_ChangeLevel = p_ChangeLevel.RCast<void(*)(CCommand & sqvm)>();

class VModTimerEngine : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
		// ideally we should change these to actually correct offsets
		// but that might change behavior slightly by a few frames
		// and because all the src mods are far-right conservatives
		// ig i just wont do that lel
		p_tickCount = g_pEngineDll->Offset(0x765A24);
		// TODO: engine.dll is only 9MB large. not even close to 330MB.
		// This probs belongs to another DLL???
		p_inCutscene = g_pEngineDll->Offset(0x111E1B58);

		p_LoadSavedGame = g_pEngineDll->Offset(0x166130);
		v_LoadSavedGame = p_LoadSavedGame.RCast<void(*)(CCommand & sqvm)>();

		p_ChangeLevel = g_pEngineDll->Offset(0x15AAD0);
		v_ChangeLevel = p_ChangeLevel.RCast<void(*)(CCommand & sqvm)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};

class VModTimerClient : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
		p_inLoadingScreen = g_pClientDll->Offset(0xB38C5C);
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }// no client.dll hooks so just define it here
	virtual void Detach(void) const { }
};

class VModTimerServer : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
		p_Script_ChangeLevel = g_pServerDll->Offset(0x2772b0);
		v_Script_ChangeLevel = p_Script_ChangeLevel.RCast<SQRESULT(*)(HSquirrelVM* sqvm)>();

		p_currentMap = g_pServerDll->Offset(0x1053370);
		v_currentMap = p_currentMap.RCast<const char*>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};