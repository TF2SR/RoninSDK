#pragma once

#include "filesystem.h"

class VDiskVMTFixes : public IDetour
{
public:
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};