#ifndef ICOMMANDLINE_H
#define ICOMMANDLINE_H

// Taken from northstar

abstract_class ICommandLine
{
public:
	// based on the defs in the 2013 source sdk, but for some reason has an extra function (may be another CreateCmdLine overload?)
	// these seem to line up with what they should be though
	virtual void CreateCmdLine(const char* commandline) {}
	virtual void CreateCmdLine(int argc, char** argv) {}
	virtual void unknown() {}
	virtual const char* GetCmdLine(void) const {}

	virtual const char* CheckParm(const char* psz, const char** ppszValue = 0) const {}
	virtual void RemoveParm() const {}
	virtual void AppendParm(const char* pszParm, const char* pszValues) {}

	virtual const char* ParmValue(const char* psz, const char* pDefaultVal = 0) const {}
	virtual int ParmValue(const char* psz, int nDefaultVal) const {}
	virtual float ParmValue(const char* psz, float flDefaultVal) const {}

	virtual int ParmCount() const {}
	virtual int FindParm(const char* psz) const {}
	virtual const char* GetParm(int nIndex) const {}
	virtual void SetParm(int nIndex, char const* pParm) {}

	// virtual const char** GetParms() const {}
};

#endif // ICOMMANDLINE_H
