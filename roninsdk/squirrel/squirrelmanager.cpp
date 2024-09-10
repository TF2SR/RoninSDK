#include "squirrelmanager.h"
#include "squirrel/sqapi.h"
#include "squirrel/sqvm.h"
#include "tier0/threadtools.h"

template class SquirrelManager<ScriptContext::SERVER>;
template class SquirrelManager<ScriptContext::CLIENT>;
template class SquirrelManager<ScriptContext::UI>;

template<ScriptContext context>
SquirrelManager<context>::SquirrelManager()
{
	m_pSQVM = nullptr;
}

/* ==== CORE FUNCS ====================================================================================================================================================== */
template<ScriptContext context>
int64 SquirrelManager<context>::RegisterFunction(CSquirrelVM* sqvm, const SQChar* scriptname, const SQChar* nativename, const SQChar* helpstring, const SQChar* returntype, const SQChar* arguments, void* functor)
{
	SQFuncRegistration func;
	memset(&func, 0, sizeof(SQFuncRegistration));
	func.squirrelFuncName = scriptname;
	func.cppFuncName = nativename;
	func.helpText = helpstring;
	func.returnTypeString = returntype;
	func.argTypes = arguments;
	func.funcPtr = functor;

	return v_sq_registerfunc<context>(sqvm, &func, 1);
}

template<ScriptContext context>
void SquirrelManager<context>::DefConst(CSquirrelVM* sqvm, const SQChar* name, int value)
{
	v_sq_defconst<context>(sqvm, name, value);
}

template<ScriptContext context>
SQRESULT SquirrelManager<context>::CompileBuffer(HSquirrelVM* sqvm, SQBufferState* compileBuffer, const char* file, int a1, SQBool bShouldThrowError)
{
	return v_sq_compilebuffer<context>(sqvm, compileBuffer, file, a1, bShouldThrowError);
}

template<ScriptContext context>
SQRESULT SquirrelManager<context>::Call(HSquirrelVM* sqvm, SQInteger iArgs, SQBool bShouldReturn, SQBool bThrowError)
{
	return v_sq_call<context>(sqvm, iArgs, bShouldReturn, bThrowError);
}

template<ScriptContext context>
SQInteger SquirrelManager<context>::RaiseError(HSquirrelVM* sqvm, const SQChar* pError)
{
	return v_sq_raiseerror<context>(sqvm, pError);
}

template<ScriptContext context>
SQBool SquirrelManager<context>::CompileFile(CSquirrelVM* sqvm, const char* path, const char* name, int a4)
{
	return v_sq_compilefile<context>(sqvm, path, name, a4);
}

/* ==== ARRAY FUNCS ===================================================================================================================================================== */
template<ScriptContext context>
void SquirrelManager<context>::NewArray(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	v_sq_newarray<context>(sqvm, iStackpos);
}

template<ScriptContext context>
SQRESULT SquirrelManager<context>::ArrayAppend(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	return v_sq_arrayappend<context>(sqvm, iStackpos);
}

/* ==== TABLE FUNCS ===================================================================================================================================================== */
template<ScriptContext context>
SQRESULT SquirrelManager<context>::NewTable(HSquirrelVM* sqvm)
{
	return v_sq_newtable<context>(sqvm);
}

template<ScriptContext context>
SQRESULT SquirrelManager<context>::NewTableSlot(HSquirrelVM* sqvm, SQInteger idx, SQBool bStatic)
{
	return v_sq_newtableslot<context>(sqvm, idx, bStatic);
}

/* ==== STACK PUSH FUNCS ================================================================================================================================================ */
template<ScriptContext context>
void SquirrelManager<context>::PushRootTable(HSquirrelVM* sqvm)
{
	v_sq_pushroottable<context>(sqvm);
}

template<ScriptContext context>
void SquirrelManager<context>::PushString(HSquirrelVM* sqvm, const SQChar* pStr, SQInteger iLength)
{
	v_sq_pushstring<context>(sqvm, pStr, iLength);
}

template<ScriptContext context>
void SquirrelManager<context>::PushInteger(HSquirrelVM* sqvm, SQInteger i)
{
	v_sq_pushinteger<context>(sqvm, i);
}

template<ScriptContext context>
void SquirrelManager<context>::PushFloat(HSquirrelVM* sqvm, SQFloat f)
{
	v_sq_pushfloat<context>(sqvm, f);
}

template<ScriptContext context>
void SquirrelManager<context>::PushBool(HSquirrelVM* sqvm, SQBool b)
{
	v_sq_pushbool<context>(sqvm, b);
}

template<ScriptContext context>
void SquirrelManager<context>::PushAsset(HSquirrelVM* sqvm, const SQChar* str, SQInteger iLength)
{
	v_sq_pushasset<context>(sqvm, str, iLength);
}

template<ScriptContext context>
void SquirrelManager<context>::PushVector(HSquirrelVM* sqvm, const SQFloat* pVec)
{
	v_sq_pushvector<context>(sqvm, pVec);
}

template<ScriptContext context>
void SquirrelManager<context>::PushObject(HSquirrelVM* sqvm, SQObject* pVec)
{
	v_sq_pushobject<context>(sqvm, pVec);
}

/* ==== STACK GET FUNCS ================================================================================================================================================= */
template<ScriptContext context>
const SQChar* SquirrelManager<context>::GetString(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	return v_sq_getstring<context>(sqvm, iStackpos);
}

template<ScriptContext context>
SQInteger SquirrelManager<context>::GetInteger(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	return v_sq_getinteger<context>(sqvm, iStackpos);
}

template<ScriptContext context>
SQFloat SquirrelManager<context>::GetFloat(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	return v_sq_getfloat<context>(sqvm, iStackpos);
}

template<ScriptContext context>
SQBool SquirrelManager<context>::GetBool(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	return v_sq_getbool<context>(sqvm, iStackpos);
}

template<ScriptContext context>
SQRESULT SquirrelManager<context>::Get(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	return v_sq_get<context>(sqvm, iStackpos);
}

template<ScriptContext context>
SQRESULT SquirrelManager<context>::GetAsset(HSquirrelVM* sqvm, SQInteger iStackpos, const char** pResult)
{
	return v_sq_getasset<context>(sqvm, iStackpos, pResult);
}

template<ScriptContext context>
SQRESULT SquirrelManager<context>::GetUserData(HSquirrelVM* sqvm, SQInteger iStackpos, void** pData, uint64* pTypeId)
{
	return v_sq_getuserdata<context>(sqvm, iStackpos, pData, pTypeId);
}

template<ScriptContext context>
SQFloat* SquirrelManager<context>::GetVector(HSquirrelVM* sqvm, SQInteger iStackpos)
{
	return v_sq_getvector<context>(sqvm, iStackpos);
}

template<ScriptContext context>
SQBool SquirrelManager<context>::GetThisEntity(HSquirrelVM* sqvm, void** ppEntity)
{
	return v_sq_getthisentity<context>(sqvm, ppEntity);
}

template<ScriptContext context>
void SquirrelManager<context>::GetObject(HSquirrelVM* sqvm, SQInteger iStackPos, SQObject* pOutObj)
{
	v_sq_getobject<context>(sqvm, iStackPos, pOutObj);
}

/* ==== MANAGER FUNCS =================================================================================================================================================== */
template<ScriptContext context>
void SquirrelManager<context>::SQVMCreated(CSquirrelVM* sqvm)
{
	m_pSQVM = sqvm;
}

template<ScriptContext context>
void SquirrelManager<context>::SQVMDestroyed()
{
	m_pSQVM = nullptr;
}

template<ScriptContext context>
void SquirrelManager<context>::ExecuteBuffer(const char* pszBuffer)
{
	if (!ThreadInMainThread())
	{
		// TODO [Fifty]: If we get here schedule call in main
		Error(eDLL_T::ENGINE, NO_ERROR, "Calling ExecuteBuffer from other threads not currently supported!\n");
		return; // Only run in main thread.
	}

	if (!m_pSQVM || !m_pSQVM->sqvm)
	{
		Error(eDLL_T::ENGINE, NO_ERROR, "Cannot execute code, %s sqvm is not initialised!\n", SQ_GetContextName(context).c_str());
		return;
	}

	DevMsg(eDLL_T::ENGINE, "Executing %s script code: '%s'\n", SQ_GetContextName(context).c_str(), pszBuffer);

	std::string strCode(pszBuffer);
	SQBufferState bufferState = SQBufferState(strCode);

	SQRESULT compileResult = CompileBuffer(m_pSQVM->sqvm, &bufferState, "console", -1, false);
	DevMsg(eDLL_T::ENGINE, "CompileBuffer returned %i\n", compileResult);

	if (compileResult != SQRESULT_ERROR)
	{
		PushRootTable(m_pSQVM->sqvm);
		SQRESULT callResult = Call(m_pSQVM->sqvm, 0, false, false);
		DevMsg(eDLL_T::ENGINE, "Call returned %i\n", compileResult);
	}
}