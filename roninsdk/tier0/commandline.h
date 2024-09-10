#pragma once

#include "public/icommandline.h"

inline CMemory p_CommandLine;
inline auto CommandLine = p_CommandLine.RCast<ICommandLine*(*)(void)>();

///////////////////////////////////////////////////////////////////////////////
class VCommandLine : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CommandLine", p_CommandLine.GetPtr());
	}
	virtual void GetFun(void) const { }
	virtual void GetVar(void) const
	{
		p_CommandLine = g_pTier0Dll->GetExportedFunction("CommandLine");
		CommandLine = p_CommandLine.RCast<ICommandLine*(*)(void)>();
	}
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////
