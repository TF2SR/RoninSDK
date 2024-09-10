#ifndef EDITABLEPANEL_H
#define EDITABLEPANEL_H

#include "vgui_controls/Panel.h"

namespace vgui
{
	class EditablePanel : public Panel
	{
	public:
		virtual void sub_18077C950();
		virtual void sub_18077C9F0();
		virtual void sub_18077D370();
		virtual void sub_18077C990();
		virtual void sub_18077BA30();
		virtual void sub_18077C250();
		virtual void sub_18077C0F0();
		virtual void sub_18077D550();
		virtual void SetControlString(const char* controlName, const char* string);
		virtual void SetControlString(const char* controlName, const wchar_t* string);
		virtual int GetControlInt(const char* controlName, int defaultState);
		virtual void GetControlString(const char* controlName, char* buf, int bufSize, const char* defaultString);
		virtual void sub_18077C2F0();
		virtual void sub_18077D3C0();
		virtual void sub_18077D5D0();
		virtual /*KeyValues*/ void* GetDialogVariables();
		virtual void sub_18077D680(); // Also GetDialogVariables???
		virtual void sub_18077D760(); // Also GetDialogVariables???
		virtual void sub_18077D610(); // Also GetDialogVariables???
		virtual void sub_18077D100();
		virtual void sub_18077C4A0();
		virtual void sub_18077CBF0();
		virtual void OnCurrentDefaultButtonSet(VPANEL defaultButton);
		virtual void OnFindDefaultButton();
		virtual void sub_18077CB30();

		_BYTE gap8[72];
		char* m_pszConfigName;
		int m_iConfigID;
	};
	static_assert(sizeof(EditablePanel) == 696);
}

///////////////////////////////////////////////////////////////////////////////
inline CMemory p_EditablePanel__EditablePanel;
inline auto v_EditablePanel__EditablePanel = p_EditablePanel__EditablePanel.RCast<vgui::EditablePanel*(*)(vgui::EditablePanel* self, vgui::Panel* pParent, const char* pszPanelName)>();

///////////////////////////////////////////////////////////////////////////////
class VguiEditablePanel : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("vgui::EditablePanel::EditablePanel", p_EditablePanel__EditablePanel.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_EditablePanel__EditablePanel = g_pClientDll->Offset(0x77B570);
		v_EditablePanel__EditablePanel = p_EditablePanel__EditablePanel.RCast<vgui::EditablePanel*(*)(vgui::EditablePanel*, vgui::Panel*, const char*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};

#endif // !EDITABLEPANEL_H