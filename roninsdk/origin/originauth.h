#pragma once

#define ORIGIN_3PTOKEN_REPLACEMENT "Protocol 3: Protect the Pilot"

inline CMemory p_Origin__Auth3PToken;
inline auto v_Origin__Auth3PToken = p_Origin__Auth3PToken.RCast<char*(*)(void)>();

inline CMemory p_Origin__AuthWithStryder;
inline auto v_Origin__AuthWithStryder = p_Origin__AuthWithStryder.RCast<void(*)(void* a1)>();

inline char* g_psz3PToken = nullptr;
inline char* g_pszLocalPlayerUserID = nullptr;
inline char* g_pszLocalPlayerOriginToken = nullptr;

///////////////////////////////////////////////////////////////////////////////
class VOrigin : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("Origin::Auth3PToken", p_Origin__Auth3PToken.GetPtr());
		LogFunAdr("Origin::AuthWithStryder", p_Origin__AuthWithStryder.GetPtr());
		LogVarAdr("g_psz3PToken", reinterpret_cast<uintptr_t>(g_psz3PToken));
		LogVarAdr("g_pszLocalPlayerUserID", reinterpret_cast<uintptr_t>(g_pszLocalPlayerUserID));
		LogVarAdr("g_pszLocalPlayerOriginToken", reinterpret_cast<uintptr_t>(g_pszLocalPlayerOriginToken));
	}
	virtual void GetFun(void) const
	{
		p_Origin__Auth3PToken = g_pEngineDll->Offset(0x183760);
		v_Origin__Auth3PToken = p_Origin__Auth3PToken.RCast<char*(*)(void)>();

		p_Origin__AuthWithStryder = g_pEngineDll->Offset(0x1843A0);
		v_Origin__AuthWithStryder = p_Origin__AuthWithStryder.RCast<void(*)(void*)>();
	}
	virtual void GetVar(void) const
	{
		g_psz3PToken = g_pEngineDll->Offset(0x13979D80).RCast<char*>();
		g_pszLocalPlayerUserID = g_pEngineDll->Offset(0x13F8E688).RCast<char*>();
		g_pszLocalPlayerOriginToken = g_pEngineDll->Offset(0x13979C80).RCast<char*>();
	}
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};