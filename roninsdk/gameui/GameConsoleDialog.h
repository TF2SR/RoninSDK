#ifndef GAMECONSOLEDIALOG_H
#define GAMECONSOLEDIALOG_H

#include "core/stdafx.h"

inline CMemory p_CGameConsoleDialog__OnCommandSubmitted;
inline auto v_CGameConsoleDialog__OnCommandSubmitted = p_CGameConsoleDialog__OnCommandSubmitted.RCast<void(*)(void*,const char*)>();

///////////////////////////////////////////////////////////////////////////////
class VConsoleDialog : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CGameConsoleDialog::OnCommandSubmitted", p_CGameConsoleDialog__OnCommandSubmitted.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CGameConsoleDialog__OnCommandSubmitted = g_pClientDll->Offset(0x4A2550); /* "48 8B 0D E9 B3 79 00 48 8B 01 48 FF A0 C8 08 00 00" */
		v_CGameConsoleDialog__OnCommandSubmitted = p_CGameConsoleDialog__OnCommandSubmitted.RCast<void(*)(void*,const char*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////

#endif /* GAMECONSOLEDIALOG_H */