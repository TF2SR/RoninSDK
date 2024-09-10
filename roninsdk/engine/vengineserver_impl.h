#ifndef VENGINESERVER_IMPL_H
#define VENGINESERVER_IMPL_H

inline CMemory p_CVEngineServer__SpewOutputFunc;
inline auto v_CVEngineServer__SpewOutputFunc = p_CVEngineServer__SpewOutputFunc.RCast<void(*)(void* pEngineServer, SpewType_t type, const char* fmt, va_list args)>();

///////////////////////////////////////////////////////////////////////////////
class VEngineServer : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CVEngineServer::SpewOutputFunc", p_CVEngineServer__SpewOutputFunc.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CVEngineServer__SpewOutputFunc = g_pEngineDll->Offset(0x11CA80);
		v_CVEngineServer__SpewOutputFunc = p_CVEngineServer__SpewOutputFunc.RCast<void(*)(void*, SpewType_t, const char*, va_list)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////

#endif /* VENGINESERVER_IMPL_H */