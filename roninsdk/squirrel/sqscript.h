#pragma once

#include "squirrel/sqdatatypes.h"
#include "squirrel/sqclasstypes.h"

///////////////////////////////////////////////////////////////////////////////

template<ScriptContext context>
inline CMemory p_CSquirrelVM_Init;
template<ScriptContext context>
inline auto v_CSquirrelVM_Init = p_CSquirrelVM_Init<context>.RCast<CSquirrelVM*(*)(void* a1, ScriptContext nSqContext)>();

template<ScriptContext context>
inline CMemory p_DestroyVM;
template<ScriptContext context>
inline auto v_DestroyVM = p_DestroyVM<context>.RCast<void (*)(void* a1, CSquirrelVM* sqvm)>();

template<ScriptContext context>
inline CMemory p_SQCompiler_Create;
template<ScriptContext context>
inline auto v_SQCompiler_Create = p_SQCompiler_Create<context>.RCast<void * (*)(HSquirrelVM * sqvm, void* a2, void* a3, SQBool bShouldThrowError)>();

///////////////////////////////////////////////////////////////////////////////
template <ScriptContext context>
CSquirrelVM* CSquirrelVM_Init(void* a1, ScriptContext nSqContext);