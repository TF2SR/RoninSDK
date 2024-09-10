#pragma once

#include "squirrel/sqdatatypes.h"
#include "squirrel/sqclasstypes.h"

abstract_class ISquirrelManager
{
public:
	// Core funcs
	virtual int64 RegisterFunction(CSquirrelVM* sqvm, const SQChar* scriptname, const SQChar* nativename, const SQChar* helpstring, const SQChar* returntype, const SQChar* arguments, void* functor) = 0;
	
	// TODO [Fifty]: Change this to be easier to use
	virtual void DefConst(CSquirrelVM* sqvm, const SQChar* name, int value) = 0;
	virtual SQRESULT CompileBuffer(HSquirrelVM* sqvm, SQBufferState* compileBuffer, const char* file, int a1, SQBool bShouldThrowError) = 0;
	virtual SQRESULT Call(HSquirrelVM* sqvm, SQInteger iArgs, SQBool bShouldReturn, SQBool bThrowError) = 0;
	virtual SQInteger RaiseError(HSquirrelVM* sqvm, const SQChar* pError) = 0;
	virtual SQBool CompileFile(CSquirrelVM* sqvm, const char* path, const char* name, int a4) = 0;

	// Array funcs
	virtual void NewArray(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;
	virtual SQRESULT ArrayAppend(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;

	// TABLE FUNCS
	virtual SQRESULT NewTable(HSquirrelVM* sqvm) = 0;
	virtual SQRESULT NewTableSlot(HSquirrelVM* sqvm, SQInteger idx, SQBool bStatic) = 0;

	// PUSH FUNCS
	virtual void PushRootTable(HSquirrelVM* sqvm) = 0;
	virtual void PushString(HSquirrelVM* sqvm, const SQChar* pStr, SQInteger iLength) = 0;
	virtual void PushInteger(HSquirrelVM* sqvm, SQInteger i) = 0;
	virtual void PushFloat(HSquirrelVM* sqvm, SQFloat f) = 0;
	virtual void PushBool(HSquirrelVM* sqvm, SQBool b) = 0;
	virtual void PushAsset(HSquirrelVM* sqvm, const SQChar* str, SQInteger iLength) = 0;
	virtual void PushVector(HSquirrelVM* sqvm, const SQFloat* pVec) = 0;
	virtual void PushObject(HSquirrelVM* sqvm, SQObject* pVec) = 0;

	// GET FUNCS
	virtual const SQChar* GetString(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;
	virtual SQInteger GetInteger(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;
	virtual SQFloat GetFloat(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;
	virtual SQBool GetBool(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;
	virtual SQRESULT Get(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;
	virtual SQRESULT GetAsset(HSquirrelVM* sqvm, SQInteger iStackpos, const char** pResult) = 0;
	virtual SQRESULT GetUserData(HSquirrelVM* sqvm, SQInteger iStackpos, void** pData, uint64* pTypeId) = 0;
	virtual SQFloat* GetVector(HSquirrelVM* sqvm, SQInteger iStackpos) = 0;
	virtual SQBool GetThisEntity(HSquirrelVM* sqvm, void** ppEntity) = 0;
	virtual void GetObject(HSquirrelVM* sqvm, SQInteger iStackPos, SQObject* pOutObj) = 0;
};

// NOTE [Fifty]: We currently don't expose any interfaces
//               Once we do expose this the version should be updated with the class
#define SQUIRRELMANAGER_CLIENT_INTERFACE_VERSION "VClientSquirrelManager001"
#define SQUIRRELMANAGER_SERVER_INTERFACE_VERSION "VServerSquirrelManager001"
#define SQUIRRELMANAGER_UI_INTERFACE_VERSION     "VUISquirrelManager001"