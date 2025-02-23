#pragma once

#include "tier1/cmd.h"

inline std::string szServerSquirrelBuffer;

void SIG_GetAdr_f(const CCommand& args);

void SQVM_ServerScript_f(const CCommand& args);
void SQVM_ServerExecuteSqBuffer_f(const CCommand& args);
void SQVM_ClientScript_f(const CCommand& args);
void SQVM_UIScript_f(const CCommand& args);