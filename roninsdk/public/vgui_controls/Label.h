#ifndef LABEL_H
#define LABEL_H

#include "vgui_controls/Panel.h"

namespace vgui
{
	class Label : public Panel
	{
	public:
		virtual void sub_18077F530();
		virtual void sub_18077F510();
		virtual void sub_18077EF70();
		virtual void sub_1807806C0();
		virtual void sub_180780A80();
		virtual void sub_18077F560();
		virtual void sub_1807806D0();
		virtual void sub_1807806E0();
		virtual void sub_18077F120();
		virtual void sub_18077F130();
		virtual void sub_1807809E0();
		virtual void sub_180780750();
		virtual void sub_18077F140();
		virtual void sub_180780780();
		virtual void sub_18077F160();
		virtual void sub_180780660();
		virtual int AddImage(/*IImage*/void* image, int offset);
		virtual void sub_180780790();
		virtual void sub_1807807E0();
		virtual void SetImagePreOffset(int index, int preOffset);
		virtual /*IImage*/void* GetImageAtIndex(int index);
		virtual int GetImageCount();
		virtual void ClearImages();
		virtual void ResetToSimpleTextImage();
		virtual void SetImageAtIndex(int index, /*IImage*/void* image, int offset);
		virtual void sub_18077F550();
		virtual int SetTextImageIndex(int newIndex);
		virtual void sub_180780CB0();
		virtual wchar_t CalculateHotkey(const wchar_t* text);
		virtual wchar_t CalculateHotkey(const char* text);
		virtual void ComputeAlignment(int& tx0, int& ty0, int& tx1, int& ty1);
		virtual void OnSetText(void* params);
		virtual void DrawDashedLine(int x0, int y0, int x1, int y1, int dashLen, int gapLen);
		virtual void sub_18077FC60();
		virtual void sub_18077EF20();
		virtual void sub_18077FBF0();
		virtual void nullsub_393();

		_BYTE gap4[140];
		_QWORD qword270;
		_BYTE gap278[40];
		_QWORD qword2A0;
		_DWORD dword2A8;
		_DWORD dword2AC;
		_BYTE gap2B0[8];
		_QWORD qword2B8;
	};
	//static_assert(sizeof(Label) == 760);
}

inline CMemory p_Label__Label;
inline auto v_Label__Label = p_Label__Label.RCast<vgui::Label * (*)(vgui::Label*, void*, const char*, const char*)>();


///////////////////////////////////////////////////////////////////////////////
class VguiLabel : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("vgui::Label::Label", p_Label__Label.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_Label__Label = g_pClientDll->Offset(0x77D9D0); /* "48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 20 49 8B F1 48 8B F9 E8 B1" */
		v_Label__Label = p_Label__Label.RCast<vgui::Label * (*)(vgui::Label*, void*, const char*, const char*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////
#endif // !LABEL_H