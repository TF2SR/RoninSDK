#ifndef THREADTOOLS_H
#define THREADTOOLS_H

#include "core/stdafx.h"

inline CMemory p_ThreadInMainThread;
inline auto ThreadInMainThread = p_ThreadInMainThread.RCast<bool(*)()>();

inline CMemory p_ThreadInServerFrameThread;
inline auto ThreadInServerFrameThread = p_ThreadInServerFrameThread.RCast<bool(*)()>();

inline CMemory p_ThreadSleep;
inline auto ThreadSleep = p_ThreadSleep.RCast<void(*)(unsigned nMilliseconds)>();

///////////////////////////////////////////////////////////////////////////////
class VThreadTools : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("ThreadInMainThread", p_ThreadInMainThread.GetPtr());
		LogFunAdr("ThreadInServerFrameThread", p_ThreadInServerFrameThread.GetPtr());
		LogFunAdr("ThreadSleep", p_ThreadSleep.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_ThreadInMainThread = g_pTier0Dll->GetExportedFunction("ThreadInMainThread");
		ThreadInMainThread = p_ThreadInMainThread.RCast<bool(*)()>();

		p_ThreadInServerFrameThread = g_pTier0Dll->GetExportedFunction("ThreadInServerFrameThread");
		ThreadInServerFrameThread = p_ThreadInServerFrameThread.RCast<bool(*)()>();

		p_ThreadSleep = g_pTier0Dll->GetExportedFunction("ThreadSleep");
		ThreadSleep = p_ThreadSleep.RCast<void(*)(unsigned nMilliseconds)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////

#endif // THREADTOOLS_H