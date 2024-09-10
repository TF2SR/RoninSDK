#pragma once

#include "vgui/VGUI.h"
#include "vgui/ISurface.h"


// "MatSystemSurface006" doesn't work so we use VGUI_Surface031 as it returns the
// same pointer
#define MAT_SYSTEM_SURFACE_INTERFACE_VERSION "VGUI_Surface031"

class IMatSystemSurface : public vgui::ISurface
{
public:
	virtual void sub_180021080() = 0;
	virtual void sub_180018000() = 0;
	virtual void sub_1800125F0() = 0;
	virtual void sub_180018060() = 0;
	virtual void nullsub_61() = 0;
	virtual void sub_18001C610() = 0;
	virtual void sub_180013110() = 0;
	virtual int DrawColoredText(vgui::HFont font, int x, int y, int r, int g, int b, int a, char* fmt, ...) = 0;
	virtual void sub_180013410() = 0;
	virtual void sub_180016490() = 0;
	virtual void sub_1800166E0() = 0;
	virtual void sub_180014B90() = 0;
	virtual void sub_180016320() = 0;
	virtual void sub_18001AA60() = 0;
	virtual void sub_180020FE0() = 0;
	virtual void sub_18001FC70() = 0;
	virtual void sub_180021460() = 0;
	virtual void sub_180016040() = 0;
	virtual void sub_180017170() = 0;
};

///////////////////////////////////////////////////////////////////////////////
// Used to display the "CLIENT HITCHED" and other messages
// Isn't in CMatSystemSurface, but i wanted to give it a place
inline CMemory p_MatSystemSurface_DrawTextPopUp;
inline auto MatSystemSurface_DrawTextPopUp = p_MatSystemSurface_DrawTextPopUp.RCast<void(*)(void* yOffset, void* self, vgui::HFont font, const char* pszText, bool bFadeOut, float& fDuration)>();

///////////////////////////////////////////////////////////////////////////////
class VMatSystemSurface : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("MatSystemSurface::DrawTextPopUp", p_MatSystemSurface_DrawTextPopUp.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_MatSystemSurface_DrawTextPopUp = g_pClientDll->Offset(0x34D2B0);
		MatSystemSurface_DrawTextPopUp = p_MatSystemSurface_DrawTextPopUp.RCast<void(*)(void*, void*, vgui::HFont, const char*, bool, float&)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////