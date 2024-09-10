#pragma once

//-------------------------------------------------------------------------
// Methods of IApplication
//-------------------------------------------------------------------------
/* ==== CAPPSYSTEMGROUP ================================================================================================================================================= */
inline CMemory p_CModAppSystemGroup__Main;
inline auto v_CModAppSystemGroup__Main = p_CModAppSystemGroup__Main.RCast<int(*)(void* pModAppSystemGroup, void *a2)>();

inline CMemory p_CModAppSystemGroup__Create;
inline auto v_CModAppSystemGroup__Create = p_CModAppSystemGroup__Create.RCast<bool(*)(void* pModAppSystemGroup)>();

///////////////////////////////////////////////////////////////////////////////
class VApplication : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CModAppSystemGroup::Main", p_CModAppSystemGroup__Main.GetPtr());
		LogFunAdr("CModAppSystemGroup::Create", p_CModAppSystemGroup__Create.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CModAppSystemGroup__Main = g_pEngineDll->Offset(0x1C64F0); /* "40 53 48 83 EC 20 80 B9 A8 00 00 00 00 48 8B 0D" */
		v_CModAppSystemGroup__Main = p_CModAppSystemGroup__Main.RCast<int(*)(void*,void*)>();

		p_CModAppSystemGroup__Create = g_pEngineDll->Offset(0x1C4E40); /* "48 89 4C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83" */
		v_CModAppSystemGroup__Create = p_CModAppSystemGroup__Create.RCast<bool(*)(void*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////
