#ifndef LISTPANEL_H
#define LISTPANEL_H

#include "public/vgui/VGUI.h"

namespace vgui
{
	class ListPanel : public Panel
	{
	public:
		virtual void sub_1807A6DD0();
		virtual void AddColumnHeader(int index, const char* columnName, const char* columnText, int startingWidth, int minWidth, int maxWidth, int columnFlags = 0);
		virtual void sub_1807AE1D0();
		virtual void sub_1807A8540();
		virtual void sub_1807AFE70();
		virtual void sub_1807AFF20();
		virtual void sub_1807AFF50();
		virtual void sub_1807AFE80();
		virtual void sub_1807AFF80();
		virtual void sub_1807B00D0();
		virtual void sub_1807A9590();
		virtual void sub_1807A9280();
		virtual void sub_1807B0890();
		virtual void sub_1807B0850();
		virtual void sub_1807B09D0();
		virtual void sub_1807B0020();
		virtual void sub_1807B00F0();
		virtual void sub_1807AFE30();
		virtual void sub_1807A7130();
		virtual void sub_1807A93D0();
		virtual void sub_1807A9390();
		virtual void sub_1807A9300();
		virtual void sub_1807A93E0();
		virtual void sub_1807A9460();
		virtual void sub_1807A94D0();
		virtual void sub_1807A9420();
		virtual void sub_1807B0910();
		virtual void sub_1807A9480();
		virtual void sub_1807A79D0();
		virtual void sub_1807AE440();
		virtual void sub_1807AF1F0();
		virtual void sub_1807AE020();
		virtual void sub_1807A83C0();
		virtual void sub_1807A9120();
		virtual void sub_1807A8B30();
		virtual void sub_1807A87F0();
		virtual void sub_1807ABC30();
		virtual void sub_1807AAFB0();
		virtual void sub_1807AB4C0();
		virtual void sub_1807B0380();
		virtual void sub_1807B02E0();
		virtual void sub_1807B01E0();
		virtual void sub_1807B0260();
		virtual void sub_1807A9630();
		virtual void sub_1807A9610();
		virtual void sub_1807A80E0();
		virtual void sub_1807A8130();
		virtual void sub_1807AB160();
		virtual void sub_1807A7310();
		virtual void sub_1807B06B0();
		virtual void sub_1807A9600();
		virtual void sub_1807B0600();
		virtual void sub_1807B0620();
		virtual void sub_1807A88C0();
		virtual void sub_1807A89E0();
		virtual void sub_1807B01B0();
		virtual void sub_1807B0180();
		virtual void sub_1807A8430();
		virtual void sub_1807AB630();
		virtual void sub_1807AB0E0();
		virtual void sub_1807AF360();
		virtual void sub_1807A8C00();
		virtual void sub_1807ACB10();
		virtual void sub_1807ABC50();
		virtual void sub_1807ACA60();
		virtual void sub_1807ACBD0();
		virtual void sub_1807ACB40();
		virtual void sub_1807A95C0();
		virtual void sub_1807A9670();
		virtual void sub_1807B0860();
		BYTE gap[300];
		// TODO [Fifty]: This is incorrect af
	};
	//static_assert(sizeof(Panel) == 608);
} // vgui

inline CMemory p_ListPanel__ListPanel;
inline auto v_ListPanel__ListPanel = p_ListPanel__ListPanel.RCast<vgui::ListPanel*(*)(vgui::ListPanel*, vgui::Panel* pParent, const char* pszPanelName)>();

///////////////////////////////////////////////////////////////////////////////
class VguiListPanel : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("vgui::ListPanel::ListPanel", p_ListPanel__ListPanel.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_ListPanel__ListPanel = g_pClientDll->Offset(0x7A5FB0);
		v_ListPanel__ListPanel = p_ListPanel__ListPanel.RCast<vgui::ListPanel*(*)(vgui::ListPanel*, vgui::Panel* pParent, const char* pszPanelName)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
#endif /* !LISTPANEL_H */