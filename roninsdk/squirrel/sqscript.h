#pragma once

#include "squirrel/sqdatatypes.h"
#include "squirrel/sqclasstypes.h"

///////////////////////////////////////////////////////////////////////////////

template<ScriptContext context>
inline CMemory p_CSquirrelVM_Init;
template<ScriptContext context>
inline auto v_CSquirrelVM_Init = p_CSquirrelVM_Init<context>.RCast<CSquirrelVM*(*)(void* a1, ScriptContext nSqContext)>();

///////////////////////////////////////////////////////////////////////////////
template <ScriptContext context>
CSquirrelVM* CSquirrelVM_Init(void* a1, ScriptContext nSqContext);