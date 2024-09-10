#pragma once

#include "squirrel/sqdatatypes.h"
#include "squirrel/sqclasstypes.h"

///////////////////////////////////////////////////////////////////////////////

template<ScriptContext context>
inline CMemory p_SQVM_PrintFunc;
template<ScriptContext context>
inline auto v_SQVM_PrintFunc = p_SQVM_PrintFunc<context>.RCast<SQRESULT(*)(HSquirrelVM * sqvm, SQChar * fmt, ...)>();

template<ScriptContext context>
inline CMemory p_SQVM_CompileError;
template<ScriptContext context>
inline auto v_SQVM_CompileError = p_SQVM_CompileError<context>.RCast<void(*)(HSquirrelVM * sqvm, const SQChar * pszError, const SQChar * pszFile, SQUnsignedInteger nLine, SQInteger nColumn)>();


///////////////////////////////////////////////////////////////////////////////
// Helper functions
eDLL_T        SQ_GetLogContext(ScriptContext nSqContext);
string        SQ_GetContextName(ScriptContext nSqContext);
ScriptContext SQ_GetVMContext(HSquirrelVM* sqvm);

///////////////////////////////////////////////////////////////////////////////
template <ScriptContext context>
SQRESULT SQVM_PrintFunc(HSquirrelVM* sqvm, SQChar* fmt, ...);

template <ScriptContext context>
void SQVM_CompileError(HSquirrelVM* sqvm, const SQChar* pszError, const SQChar* pszFile, SQUnsignedInteger nLine, SQInteger nColumn);