#pragma once

/* ==== CFPSPANEL ======================================================================================================================================================= */
inline CMemory p_CFPSPanel_Paint;
inline auto v_CFPSPanel_Paint = p_CFPSPanel_Paint.RCast<void*(*)(void* self)>();

///////////////////////////////////////////////////////////////////////////////
class VFPSPanel : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CFPSPanel::Paint", p_CFPSPanel_Paint.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CFPSPanel_Paint = g_pClientDll->Offset(0x34D980);
		v_CFPSPanel_Paint = p_CFPSPanel_Paint.RCast<void*(*)(void*)>(); 
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////