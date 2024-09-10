#ifndef VGUI_BASEUI_INTERFACE_H
#define VGUI_BASEUI_INTERFACE_H

#include "core/stdafx.h"
#include "vguimatsurface/MatSystemSurface.h"


extern IMatSystemSurface* g_pMatSystemSurface;

///////////////////////////////////////////////////////////////////////////////

inline CMemory p_CEngineVGui__Init;
inline auto v_CEngineVGui__Init = p_CEngineVGui__Init.RCast<char(*)(void*)>();

inline CMemory p_CEngineVGui__Shutdown;
inline auto v_CEngineVGui__Shutdown = p_CEngineVGui__Shutdown.RCast<void(*)(void*)>();

///////////////////////////////////////////////////////////////////////////////
class VEngineVgui : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CEngineVgui::Init", p_CEngineVGui__Init.GetPtr());
		LogFunAdr("CEngineVgui::Shutdown", p_CEngineVGui__Shutdown.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CEngineVGui__Init = g_pEngineDll->Offset(0x247E10); /* "40 53 57 48 83 EC 38 48 8B F9 FF 15 38 6E 37 00" */
		v_CEngineVGui__Init = p_CEngineVGui__Init.RCast<char(*)(void*)>();

		p_CEngineVGui__Shutdown = g_pEngineDll->Offset(0x249A70); /* "48 89 5C 24 08 57 48 83  EC 20 48 8B D9 48 8B 89 08 01" */
		v_CEngineVGui__Shutdown = p_CEngineVGui__Shutdown.RCast<void(*)(void*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////

#endif /* VGUI_BASEUI_INTERFACE_H */
