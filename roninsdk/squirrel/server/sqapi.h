#pragma once
// SERVER

#include "squirrel/sqapi.h"

///////////////////////////////////////////////////////////////////////////////
class VSqapi_SERVER : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
		// CORE FUNCS
		p_sq_registerfunc<ScriptContext::SERVER> = g_pServerDll->Offset(0x1DD10);
		p_sq_defconst<ScriptContext::SERVER> = g_pServerDll->Offset(0x1F550);
		p_sq_compilebuffer<ScriptContext::SERVER> = g_pServerDll->Offset(0x3110);
		p_sq_call<ScriptContext::SERVER> = g_pServerDll->Offset(0x8620);
		p_sq_raiseerror<ScriptContext::SERVER> = g_pServerDll->Offset(0x8440);
		p_sq_compilefile<ScriptContext::SERVER> = g_pServerDll->Offset(0x1CD80);

		v_sq_registerfunc<ScriptContext::SERVER> = p_sq_registerfunc<ScriptContext::SERVER>.RCast<int64_t(*)(CSquirrelVM* sqvm, SQFuncRegistration* funcReg, char unknown)>();
		v_sq_defconst<ScriptContext::SERVER> = p_sq_defconst<ScriptContext::SERVER>.RCast<void(*)(CSquirrelVM* sqvm, const SQChar* name, int value)>();
		v_sq_compilebuffer<ScriptContext::SERVER> = p_sq_compilebuffer<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm, SQBufferState* compileBuffer, const char* file, int a1, SQBool bShouldThrowError)>();
		v_sq_call<ScriptContext::SERVER> = p_sq_call<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm, SQInteger iArgs, SQBool bShouldReturn, SQBool bThrowError)>();
		v_sq_raiseerror<ScriptContext::SERVER> = p_sq_raiseerror<ScriptContext::SERVER>.RCast<SQInteger(*)(HSquirrelVM* sqvm, const SQChar* pError)>();
		v_sq_compilefile<ScriptContext::SERVER> = p_sq_compilefile<ScriptContext::SERVER>.RCast<SQBool(*)(CSquirrelVM* sqvm, const char* path, const char* name, int a4)>();

		// ARRAY FUNCS
		p_sq_newarray<ScriptContext::SERVER> = g_pServerDll->Offset(0x39F0);
		p_sq_arrayappend<ScriptContext::SERVER> = g_pServerDll->Offset(0x3C70);

		v_sq_newarray<ScriptContext::SERVER> = p_sq_newarray<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();
		v_sq_arrayappend<ScriptContext::SERVER> = p_sq_arrayappend<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();

		// TABLE FUNCS
		p_sq_newtable<ScriptContext::SERVER> = g_pServerDll->Offset(0x3960);
		p_sq_newtableslot<ScriptContext::SERVER> = g_pServerDll->Offset(0x7080);

		v_sq_newtable<ScriptContext::SERVER> = p_sq_newtable<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm)>();
		v_sq_newtableslot<ScriptContext::SERVER> = p_sq_newtableslot<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm, SQInteger idx, SQBool bStatic)>();

		// PUSH FUNCS
		p_sq_pushroottable<ScriptContext::SERVER> = g_pServerDll->Offset(0x5840);
		p_sq_pushstring<ScriptContext::SERVER> = g_pServerDll->Offset(0x3440);
		p_sq_pushinteger<ScriptContext::SERVER> = g_pServerDll->Offset(0x36A0);
		p_sq_pushfloat<ScriptContext::SERVER> = g_pServerDll->Offset(0x3800);
		p_sq_pushbool<ScriptContext::SERVER> = g_pServerDll->Offset(0x3710);
		p_sq_pushasset<ScriptContext::SERVER> = g_pServerDll->Offset(0x3560);
		p_sq_pushvector<ScriptContext::SERVER> = g_pServerDll->Offset(0x3780);
		p_sq_pushobject<ScriptContext::SERVER> = g_pServerDll->Offset(0x83A0);

		v_sq_pushroottable<ScriptContext::SERVER> = p_sq_pushroottable<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm)>();
		v_sq_pushstring<ScriptContext::SERVER> = p_sq_pushstring<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, const SQChar* pStr, SQInteger iLength)>();
		v_sq_pushinteger<ScriptContext::SERVER> = p_sq_pushinteger<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, SQInteger i)>();
		v_sq_pushfloat<ScriptContext::SERVER> = p_sq_pushfloat<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, SQFloat f)>();
		v_sq_pushbool<ScriptContext::SERVER> = p_sq_pushbool<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, SQBool b)>();
		v_sq_pushasset<ScriptContext::SERVER> = p_sq_pushasset<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, const SQChar* str, SQInteger iLength)>();
		v_sq_pushvector<ScriptContext::SERVER> = p_sq_pushvector<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, const SQFloat* pVec)>();
		v_sq_pushobject<ScriptContext::SERVER> = p_sq_pushobject<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, SQObject* pVec)>();

		// GET FUNCS
		p_sq_getstring<ScriptContext::SERVER> = g_pServerDll->Offset(0x60A0);
		p_sq_getinteger<ScriptContext::SERVER> = g_pServerDll->Offset(0x60C0);
		p_sq_getfloat<ScriptContext::SERVER> = g_pServerDll->Offset(0x60E0);
		p_sq_getbool<ScriptContext::SERVER> = g_pServerDll->Offset(0x6110);
		p_sq_get<ScriptContext::SERVER> = g_pServerDll->Offset(0x7C00);
		p_sq_getasset<ScriptContext::SERVER> = g_pServerDll->Offset(0x5FF0);
		p_sq_getuserdata<ScriptContext::SERVER> = g_pServerDll->Offset(0x63B0);
		p_sq_getvector<ScriptContext::SERVER> = g_pServerDll->Offset(0x6120);
		p_sq_getthisentity<ScriptContext::SERVER> = g_pServerDll->Offset(0x203B0);
		p_sq_getobject<ScriptContext::SERVER> = g_pServerDll->Offset(0x6140);
		p_sq_createscriptinstance<ScriptContext::SERVER> = g_pServerDll->Offset(0x43F2F0);
		p_sq_getentityfrominstance<ScriptContext::SERVER> = g_pServerDll->Offset(0x1E920);
		p_sq_getfunction<ScriptContext::SERVER> = g_pServerDll->Offset(0x6C80);
		p_sq_GetEntityConstant_CBaseEntity<ScriptContext::SERVER> = g_pServerDll->Offset(0x418AF0);

		v_sq_getstring<ScriptContext::SERVER> = p_sq_getstring<ScriptContext::SERVER>.RCast<const SQChar* (*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();
		v_sq_getinteger<ScriptContext::SERVER> = p_sq_getinteger<ScriptContext::SERVER>.RCast<SQInteger(*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();
		v_sq_getfloat<ScriptContext::SERVER> = p_sq_getfloat<ScriptContext::SERVER>.RCast<SQFloat(*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();
		v_sq_getbool<ScriptContext::SERVER> = p_sq_getbool<ScriptContext::SERVER>.RCast<SQBool(*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();
		v_sq_get<ScriptContext::SERVER> = p_sq_get<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();
		v_sq_getasset<ScriptContext::SERVER> = p_sq_getasset<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm, SQInteger iStackpos, const char** pResult)>();
		v_sq_getuserdata<ScriptContext::SERVER> = p_sq_getuserdata<ScriptContext::SERVER>.RCast<SQRESULT(*)(HSquirrelVM* sqvm, SQInteger iStackpos, void** pData, uint64_t* pTypeId)>();
		v_sq_getvector<ScriptContext::SERVER> = p_sq_getvector<ScriptContext::SERVER>.RCast<SQFloat* (*)(HSquirrelVM* sqvm, SQInteger iStackpos)>();
		v_sq_getthisentity<ScriptContext::SERVER> = p_sq_getthisentity<ScriptContext::SERVER>.RCast<SQBool(*)(HSquirrelVM* sqvm, void** ppEntity)>();
		v_sq_getobject<ScriptContext::SERVER> = p_sq_getobject<ScriptContext::SERVER>.RCast<void(*)(HSquirrelVM* sqvm, SQInteger iStackPos, SQObject* pOutObj)>();
		v_sq_createscriptinstance<ScriptContext::SERVER> = p_sq_createscriptinstance<ScriptContext::SERVER>.RCast<SQObject* (*)(void** ent)>();
		v_sq_getentityfrominstance<ScriptContext::SERVER> = p_sq_getentityfrominstance<ScriptContext::SERVER>.RCast<void*(*)(CSquirrelVM * sqvm, SQObject* pInstance, char** ppEntityContstant)>();
		v_sq_getfunction<ScriptContext::SERVER> = p_sq_getfunction<ScriptContext::SERVER>.RCast<SQBool (*)(HSquirrelVM * sqvm, const char* name, SQObject * returnObj, const char* signature)>();
		v_sq_GetEntityConstant_CBaseEntity<ScriptContext::SERVER> = p_sq_GetEntityConstant_CBaseEntity<ScriptContext::SERVER>.RCast<char** (*)()>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////