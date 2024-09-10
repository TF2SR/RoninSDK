#pragma once

inline CMemory p_CClient__Connect;
inline auto v_CClient__Connect = p_CClient__Connect.RCast<bool(*)(void* self, const char* szName, void* pNetChannel, bool bFakePlayer, void* a5, char* szMessage, void* a7)>();

///////////////////////////////////////////////////////////////////////////////
class VClient : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CClient::Connect", p_CClient__Connect.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CClient__Connect = g_pEngineDll->Offset(0x101740);
		v_CClient__Connect = p_CClient__Connect.RCast<bool(*)(void* self, const char* szName, void* pNetChannel, bool bFakePlayer, void* a5, char* szMessage, void* a7)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////