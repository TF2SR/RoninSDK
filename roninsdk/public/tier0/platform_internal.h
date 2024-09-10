#ifndef PLATFORM_INTERNAL_H
#define PLATFORM_INTERNAL_H

#include "core/stdafx.h"

inline CMemory p_Plat_FloatTime;
inline auto v_Plat_FloatTime = p_Plat_FloatTime.RCast<double(*)(void)>();

inline CMemory p_Plat_MSTime;
inline auto v_Plat_MSTime = p_Plat_MSTime.RCast<uint64_t(*)(void)>();

///////////////////////////////////////////////////////////////////////////////
class VPlatform : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("Plat_FloatTime", p_Plat_FloatTime.GetPtr());
		LogFunAdr("Plat_MSTime", p_Plat_MSTime.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_Plat_FloatTime = g_pTier0Dll->GetExportedFunction("Plat_FloatTime");
		v_Plat_FloatTime = p_Plat_FloatTime.RCast<double(*)(void)>();

		p_Plat_MSTime = g_pTier0Dll->GetExportedFunction("Plat_MSTime");
		v_Plat_MSTime = p_Plat_MSTime.RCast<uint64_t(*)(void)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////

#endif /* PLATFORM_INTERNAL_H */