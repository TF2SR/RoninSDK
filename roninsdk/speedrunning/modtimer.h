#include "squirrel/sqclasstypes.h"
#include "squirrel/sqdatatypes.h"
#include "squirrel/squirrelmanager.h"

void ModTimer_RegisterFuncs_UI(CSquirrelVM* sqvm);

inline CMemory p_ChangeLevel;
inline auto v_ChangeLevel = p_ChangeLevel.RCast<SQRESULT(*)(HSquirrelVM* sqvm)>();

inline CMemory p_inLoadingScreen;
inline CMemory p_tickCount;
inline CMemory p_inCutscene;

class VModTimerEngine : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
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
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};

class VModTimerServer : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};