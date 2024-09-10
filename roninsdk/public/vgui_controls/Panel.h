#ifndef PANEL_H
#define PANEL_H

#include "public/vgui/VGUI.h"

namespace vgui
{

	class Panel// : public IClientPanel
	{
	public:
		// IClientPanel:
		virtual VPANEL GetVPanel();
		virtual void nullsub_144();
		virtual void sub_180771E20();
		virtual void sub_18076B7E0();
		virtual void sub_18076ADE0();
		virtual void sub_18076DDB0();
		virtual void sub_180765BE0();
		virtual void sub_18075BE80();
		virtual void sub_18075B680();
		virtual void nullsub_83();
		virtual void sub_18076A580();
		virtual void nullsub_145();
		virtual void nullsub_146();
		virtual void sub_18076DF20(); // char __fastcall sub_18076DF20(_QWORD *a1, __int64 a2)
		virtual void sub_18076DDF0();
		virtual void sub_18076DEA0(); // __int64 __fastcall sub_18076DEA0(__int64 a1)
		virtual void sub_18076DE20(); // __int64 __fastcall sub_18076DE20(__int64 a1)
		virtual void OnMessage(const /*KeyValues*/void* params, VPANEL ifromPanel);
		virtual VPANEL GetCurrentKeyFocus();

		virtual void sub_18075D7D0();
		virtual void sub_180764C10();

		virtual const char* GetName();
		virtual const char* GetClassName();

		virtual HScheme GetScheme();
		virtual bool IsProportional();
		virtual bool IsAutoDeleteSet();
		virtual void DeletePanel();
		virtual void* QueryInterface(/*EInterfaceID*/ int id);
		virtual Panel* GetPanel();
		virtual void GetModuleName();
		virtual void OnTick();

		// Panel:
		// Constructors + Destructor ??
		virtual void sub_18022F000();
		virtual void sub_18022EE80();
		virtual void sub_18022EF00();
		virtual void sub_18009DC60();
		virtual void sub_1807555C0();

		virtual void SetVisible(bool state);
		virtual bool IsVisible();
		virtual void sub_180764DB0(); // __int64 __fastcall sub_180764DB0(__int64 (__fastcall ***a1)(_QWORD))
		virtual void sub_18076C140();
		virtual void sub_18076C1C0();
		virtual void nullsub_147();
		virtual void sub_18075CE00();
		virtual void sub_18075D890();
		virtual void sub_1807712D0();
		virtual void sub_180771280();
		virtual void sub_18075E900(); // char __fastcall sub_18075E900(__int64 (__fastcall ***a1)(_QWORD), __int64 a2)
		virtual void sub_18009EC30();

		virtual void SetAutoDelete(bool state);

		// messaging
		virtual void AddActionSignalTarget(Panel* messageTarget);
		virtual void AddActionSignalTarget(VPANEL messageTarget);
		virtual void RemoveActionSignalTarget(Panel* oldTarget);
		virtual void PostActionSignal(void* message);
		virtual void RequestInfoFromChild(const char* childName, void* outputData);
		virtual void PostMessageToChild(const char* childName, void* message);
		virtual void sub_1807709D0();
		virtual void sub_180771780(); // SetSilentMode?
		virtual void sub_1807630D0();
		virtual void sub_180770920();

		virtual void sub_180764CC0();

		virtual void sub_180765370(); // __int64 __fastcall sub_180765370(__int64 (__fastcall ***a1)(_QWORD))
		virtual void sub_180766DA0(); // __int64 __fastcall sub_180766DA0(__int64 (__fastcall ***a1)(__int64))
		virtual void sub_18076FE80(int unk);
		virtual void sub_1807709B0(int unk);
		virtual void SetUnk(int unk);
		virtual int GetUnk(); // 2
		virtual void sub_18075E8B0();
		virtual void sub_180099DF0();
		virtual void sub_180764770();
		virtual void sub_1807718A0();
		virtual void sub_18076FEA0();
		virtual void sub_unk();// ? _OriginalCollection@_TaskCollection@details@Concurrency@@AEBAPEAV123@XZ; Concurrency::details::_TaskCollection::_OriginalCollection(virtual void)
		virtual void SetPaintBorderEnabled(bool state);
		virtual void SetPaintBackgroundEnabled(bool state);
		virtual void SetPaintEnabled(bool state);
		virtual void SetPostChildPaintEnabled(bool state);
		virtual void sub_1807711B0(); // setter
		virtual void sub_18075C8C0(); // __int64 __fastcall sub_18075C8C0(__int64 a1, _DWORD *a2, _DWORD *a3) // 128, 66????
		virtual void sub_180770010();
		virtual void sub_1807649F0();
		virtual void sub_180764C30();
		virtual void sub_180764C50();
		virtual void sub_180766D10();
		virtual void sub_180765030();
		virtual void sub_18075E8F0();
		virtual void sub_180765310();
		virtual void sub_1807716E0();
		virtual void sub_1807716F0();
		virtual void sub_18075D0E0();
		virtual void sub_18075D0B0();
		virtual void sub_180756430();
		virtual void ApplySettings(void* inResourceData);
		virtual void sub_18076A9C0(); // __int64 __fastcall sub_18076A9C0(__int64 a1, __int64 a2)
		virtual void GetSettings(void* outResourceData);
		virtual const char* GetDescription();
		virtual void nullsub_148();
		virtual void nullsub_149();
		virtual void sub_18075E960();
		virtual void sub_180767CB0();
		virtual void sub_180769870();
		virtual void sub_18076A520();
		virtual void sub_180769070();
		virtual void sub_1807683A0();
		virtual void sub_18076A660();
		virtual void OnCursorMoved(int x, int y);
		virtual void nullsub_85();
		virtual void nullsub_86();
		virtual void nullsub_87();
		virtual void nullsub_102();
		virtual void nullsub_88();
		virtual void sub_180769910();

		virtual void SetTriplePressAllowed(bool state);
		virtual bool IsTriplePressAllowed();
		virtual void OnMouseTriplePressed(/*MouseCode*/ int code);

		virtual void sub_180770A10();
		virtual void sub_18075BF40();
		virtual void sub_180765AB0();
		virtual void sub_180764F60();
		virtual void sub_180764F50();
		virtual void sub_1807557A0();
		virtual void nullsub_150();
		virtual void sub_18075BFD0();
		virtual void sub_18075C0E0();
		virtual void sub_180768BF0();
		virtual void sub_180768E60();
		virtual void sub_180769020();
		virtual void sub_180768E10();
		virtual void sub_180768FD0();
		virtual void sub_180769890();
		virtual void sub_18076AA30();
		virtual void Paint();
		virtual void sub_18076ACB0();
		virtual void sub_18076ACF0(); // __int64 __fastcall sub_18076ACF0(__int64 (__fastcall ***a1)(_QWORD))
		virtual void nullsub_92();
		virtual void sub_18076B9E0();
		virtual void sub_18075CB00();
		virtual void sub_180771550(); // SetProportional ?
		virtual void sub_180770E30();
		virtual void sub_180770B30();
		virtual void sub_1807652D0(); // __int64 __fastcall sub_1807652D0(__int64 (__fastcall ***a1)(_QWORD))
		virtual void sub_180764F10();
		virtual void sub_1807593F0();
		virtual void sub_1807588A0();
		virtual void sub_180758C40();
		virtual void sub_1807591C0();
		virtual void sub_180759180();

		virtual void SetDragEnabled(bool enabled);
		virtual bool IsDragEnabled();

		virtual void SetShowDragHelper(bool enabled);

		virtual void OnDragFailed(/*CUtlVector< KeyValues* >&*/ void* msglist);

		virtual void SetBlockDragChaining(bool block);
		virtual bool IsBlockingDragChaining();

		// Unsure about these two
		virtual int GetDragStartTolerance();
		virtual void SetDragSTartTolerance(int nTolerance);

		virtual void SetDropEnabled(bool enabled, float m_flHoverContextTime = 0.0f);
		virtual bool IsDropEnabled();

		virtual void GetDropContextMenu(/*Menu*/ void* menu, /*CUtlVector< KeyValues* >&*/ void* msglist);
		virtual void nullsub_152(); // OnDropContextHoverShow
		virtual void nullsub_153(); // OnDropContextHoverHide

		virtual void *GetDragDropInfo();

		virtual void nullsub_154(); // OnGetAdditionalDragPanels ?
		virtual void nullsub_84(); // OnCreateDragData ?
		virtual void sub_180764CB0(); // IsDroppable ?

		virtual void OnDraggablePanelPaint();

		virtual void OnDroppablePanelPaint( /*CUtlVector< KeyValues * >&*/ void *msglist, /*CUtlVector< Panel * >&*/ void *dragPanels);

		virtual void OnPanelDropped(/*CUtlVector< KeyValues* >&*/ void* data);
		virtual void OnPanelEnteredDroppablePanel(/*CUtlVector< KeyValues* >&*/void* msglist);
		virtual void OnPanelExitedDroppablePanel(/*CUtlVector< KeyValues* >&*/void* msglist);

		virtual Panel* GetDropTarget(/*CUtlVector< KeyValues* >&*/void* msglist);

		virtual Panel* GetDragPanel();
		virtual bool IsBeingDragged();
		virtual HCursor GetDropCursor(/*CUtlVector< KeyValues* >&*/void* msglist);

		virtual void sub_18009D2E0(); // returns 13

		virtual bool CanStartDragging(int startx, int starty, int mx, int my);

		virtual void FillRectSkippingPanel(const Color& clr, int x, int y, int w, int h, Panel* skipPanel);

		virtual int GetPaintBackgroundType();
		virtual void GetCornerTextureSize(int &x, int &y);

		virtual void sub_180771870();
		virtual void sub_1807671E0();
		virtual void sub_180766E20();
		virtual void sub_180766FF0();
		virtual void sub_180767040();

		virtual void NavigateTo();
		virtual void NavigateFrom();

		virtual void sub_180767100();
		virtual void nullsub_158();
		virtual void nullsub_159();
		virtual void sub_18009DFC0();
		virtual void sub_18009E090();
		virtual void sub_18009DFD0();
		virtual void sub_18009DFE0();
		virtual void sub_18009E150();
		virtual void sub_18009E050();
		virtual void sub_18009E110();
		virtual void sub_18009E100();
		virtual void sub_18009E0A0();
		virtual void sub_18009E170();
		virtual void sub_18009E130();
		virtual void sub_18009E140();
		virtual void sub_18009D2D0();
		virtual void sub_18076A590();
		virtual void sub_180767D00();
		virtual void OnFinishDragging(bool mousereleased, /*MouseCode*/ int code, bool abort);
		virtual void sub_1807586A0();
		virtual void sub_18075BB60();
		virtual void sub_180758070();
		virtual void sub_18076A250();
		virtual void OnScreenSizeChanged(int nOldWide, int nOldTall);
		virtual void sub_1807633F0();
		virtual void sub_180763310();
		virtual void sub_180763390();
		virtual void sub_180763EE0();
		virtual void sub_180763D70();
		virtual void sub_1807641D0();
		virtual void sub_180764010();
		virtual void sub_180764250();

		virtual void InternalKeyCodePressed(int code);
		virtual void InternalKeyCodeTyped(int code);
		virtual void InternalKeyTyped(int unichar);
		virtual void InternalKeyCodeReleased(int code);

		virtual void sub_180763C80();
		virtual void sub_180763E40();
		virtual void sub_1807638D0();
		virtual void sub_1807642B0(); // calls a func with two 0 as arguments
		virtual void sub_18075D760(); // 2 in pointers, defaults to setting them to 5??
		virtual void sub_18075D6E0(); // 4 in args
		virtual void sub_18009D080(); // returns -1
		virtual void nullsub_160();
		virtual void nullsub_161();
		virtual void sub_18009DAB0(); // returns 0

		_BYTE gap4[600];
	};
	static_assert(sizeof(Panel) == 608);
	// [Fifty]: ^ Tested using a debugger and CBitmapImagePanel in a debugger
	//          so unless CBitmapImagePanel is wrong this is correct

} // vgui

inline CMemory p_Panel__Panel;
inline auto v_Panel__Panel = p_Panel__Panel.RCast<vgui::Panel*(*)(vgui::Panel*, void*)>();

///////////////////////////////////////////////////////////////////////////////
class VguiPanel : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("vgui::Panel::Panel", p_Panel__Panel.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_Panel__Panel = g_pClientDll->Offset(0x752900); /* "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 48 8D 05 02 63 27 00" */
		v_Panel__Panel = p_Panel__Panel.RCast<vgui::Panel * (*)(vgui::Panel*, void*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
#endif /* !PANEL_H */