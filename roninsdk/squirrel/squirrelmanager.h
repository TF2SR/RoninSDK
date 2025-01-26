#pragma once

#include "sqapi.h"
#include "isquirrelmanager.h"

template<ScriptContext context>
class SquirrelManager : public ISquirrelManager
{
public:
	SquirrelManager();

	// Core funcs
	virtual int64 RegisterFunction(CSquirrelVM* sqvm, const SQChar* scriptname, const SQChar* nativename, const SQChar* helpstring, const SQChar* returntype, const SQChar* arguments, void* functor);
	virtual int64 RegisterFunction(CSquirrelVM* sqvm, const SQChar* scriptname, const SQChar* returntype, const SQChar* arguments, void* functor);
	virtual void DefConst(CSquirrelVM* sqvm, const SQChar* name, int value);
	virtual SQRESULT CompileBuffer(HSquirrelVM* sqvm, SQBufferState* compileBuffer, const char* file, int a1, SQBool bShouldThrowError);
	virtual SQRESULT Call(HSquirrelVM* sqvm, SQInteger iArgs, SQBool bShouldReturn, SQBool bThrowError);
	virtual SQInteger RaiseError(HSquirrelVM* sqvm, const SQChar* pError);
	virtual SQBool CompileFile(CSquirrelVM* sqvm, const char* path, const char* name, int a4);

	// Array funcs
	virtual void NewArray(HSquirrelVM* sqvm, SQInteger iStackpos);
	virtual SQRESULT ArrayAppend(HSquirrelVM* sqvm, SQInteger iStackpos);

	// TABLE FUNCS
	virtual SQRESULT NewTable(HSquirrelVM* sqvm);
	virtual SQRESULT NewTableSlot(HSquirrelVM* sqvm, SQInteger idx, SQBool bStatic);

	// PUSH FUNCS
	virtual void PushRootTable(HSquirrelVM* sqvm);
	virtual void PushString(HSquirrelVM* sqvm, const SQChar* pStr, SQInteger iLength);
	virtual void PushInteger(HSquirrelVM* sqvm, SQInteger i);
	virtual void PushFloat(HSquirrelVM* sqvm, SQFloat f);
	virtual void PushBool(HSquirrelVM* sqvm, SQBool b);
	virtual void PushAsset(HSquirrelVM* sqvm, const SQChar* str, SQInteger iLength);
	virtual void PushVector(HSquirrelVM* sqvm, const SQFloat* pVec);
	virtual void PushObject(HSquirrelVM* sqvm, SQObject* pVec);

	// GET FUNCS
	virtual const SQChar* GetString(HSquirrelVM* sqvm, SQInteger iStackpos);
	virtual SQInteger GetInteger(HSquirrelVM* sqvm, SQInteger iStackpos);
	virtual SQFloat GetFloat(HSquirrelVM* sqvm, SQInteger iStackpos);
	virtual SQBool GetBool(HSquirrelVM* sqvm, SQInteger iStackpos);
	virtual SQRESULT Get(HSquirrelVM* sqvm, SQInteger iStackpos);
	virtual SQRESULT GetAsset(HSquirrelVM* sqvm, SQInteger iStackpos, const char** pResult);
	virtual SQRESULT GetUserData(HSquirrelVM* sqvm, SQInteger iStackpos, void** pData, uint64* pTypeId);
	virtual SQFloat* GetVector(HSquirrelVM* sqvm, SQInteger iStackpos);
	virtual SQBool GetThisEntity(HSquirrelVM* sqvm, void** ppEntity);
	virtual void GetObject(HSquirrelVM* sqvm, SQInteger iStackPos, SQObject* pOutObj);
	virtual int GetFunction(HSquirrelVM* sqvm, const char* name, SQObject* returnObj, const char* signature);
	virtual SQObject* CreateScriptInstance(void** ent);
	virtual SQStackInfos* GetStackInfos(int level);

	template <typename T> inline T* GetEntity(HSquirrelVM* sqvm, SQInteger iStackPos)
	{
		SQObject obj;
		GetObject(sqvm, iStackPos, &obj);

		// there are entity constants for other types, but seemingly CBaseEntity's is the only one needed
		return (T*)v_sq_getentityfrominstance<context>(m_pSQVM, &obj, v_sq_GetEntityConstant_CBaseEntity<context>());
	}

	// Utility
	bool PushFuncOntoStack(const char* funcname);

	void SQVMCreated(CSquirrelVM* sqvm);
	void SQVMDestroyed();

	void ExecuteBuffer(const char* pszBuffer);
	void ExecuteBuffer(const char* pszBuffer, bool printStuff);

	bool fatalCompileErrors = true;
	CSquirrelVM* m_pSQVM;
};

template<ScriptContext context>
inline SquirrelManager<context>* g_pSQManager;