#ifndef ICVAR_H
#define ICVAR_H
#include "tier0/annotations.h"
#include "appframework/IAppSystem.h"
#include "tier1/interface.h"
#include "public/iconvar.h"
#include "mathlib/color.h"
#if 1
//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class ConCommandBase;
class ConCommand;
class ConVar;
class IAppSystem;
class Color;

//-----------------------------------------------------------------------------
// ConVars/ComCommands are marked as having a particular DLL identifier
//-----------------------------------------------------------------------------
typedef int CVarDLLIdentifier_t;

//-----------------------------------------------------------------------------
// ConVars/ComCommands are marked as having a particular DLL identifier
//-----------------------------------------------------------------------------
typedef int CVarDLLIdentifier_t;

//-----------------------------------------------------------------------------
// Used to display console messages
//-----------------------------------------------------------------------------
abstract_class IConsoleDisplayFunc
{
public:
	virtual void ColorPrint(const Color& clr, const char* pMessage) = 0;
	virtual void Print(const char* pMessage) = 0;
	virtual void DPrint(const char* pMessage) = 0;
};

//-----------------------------------------------------------------------------
// Purpose: Applications can implement this to modify behavior in ICvar
//-----------------------------------------------------------------------------
#define CVAR_QUERY_INTERFACE_VERSION "VCvarQuery001"
abstract_class ICvarQuery : public IAppSystem
{
public:
	// Can these two convars be aliased?
	virtual bool AreConVarsLinkable(const ConVar * child, const ConVar * parent) = 0;
};

//-----------------------------------------------------------------------------
// Purpose: DLL interface to ConVars/ConCommands
//-----------------------------------------------------------------------------
/*
.rdata:000000018005B598                 dq offset sub_180009DA0
.rdata:000000018005B5A0                 dq offset ICvar__RegisterConCommand
.rdata:000000018005B5A8                 dq offset ICvar__UnregisterConCommand
.rdata:000000018005B5B0                 dq offset sub_18000F800
.rdata:000000018005B5B8                 dq offset sub_18000AE20
.rdata:000000018005B5C0                 dq offset sub_18000A9D0
.rdata:000000018005B5C8                 dq offset sub_18000A980
.rdata:000000018005B5D0                 dq offset sub_18000ABF0
.rdata:000000018005B5D8                 dq offset sub_18000ABB0
.rdata:000000018005B5E0                 dq offset sub_18000A940
.rdata:000000018005B5E8                 dq offset sub_18000A900
.rdata:000000018005B5F0                 dq offset sub_18000CF30
.rdata:000000018005B5F8                 dq offset sub_18000E6F0
.rdata:000000018005B600                 dq offset sub_18000C200
.rdata:000000018005B608                 dq offset sub_18000E610
.rdata:000000018005B610                 dq offset sub_180009DE0
.rdata:000000018005B618                 dq offset sub_18000C190
.rdata:000000018005B620                 dq offset sub_18000E5A0
.rdata:000000018005B628                 dq offset sub_180009FD0
.rdata:000000018005B630                 dq offset sub_18000A170
.rdata:000000018005B638                 dq offset sub_18000A0B0
.rdata:000000018005B640                 dq offset sub_18000EC50
.rdata:000000018005B648                 dq offset sub_18000C170
.rdata:000000018005B650                 dq offset sub_18000F4B0
.rdata:000000018005B658                 dq offset ?Id@SchedulingRing@details@Concurrency@@QEBAHXZ ; Concurrency::details::SchedulingRing::Id(void)
.rdata:000000018005B660                 dq offset sub_18000AEB0
.rdata:000000018005B668                 dq offset sub_18000AEC0
.rdata:000000018005B670                 dq offset sub_18000C530
.rdata:000000018005B678                 dq offset sub_18000DD60
.rdata:000000018005B680                 dq offset sub_18000DCD0
.rdata:000000018005B688                 dq offset sub_18000DDF0
.rdata:000000018005B690                 dq offset sub_18000B8A0
.rdata:000000018005B698                 dq offset sub_18000D3C0
.rdata:000000018005B6A0                 dq offset sub_18000A550
*/
abstract_class ICvar : public IAppSystem
{
public:
	virtual CVarDLLIdentifier_t AllocateDLLIdentifier() = 0;

	// Register, unregister commands
	virtual void RegisterConCommand(ConCommandBase* pCommandBase) = 0;
	virtual void UnregisterConCommand(ConCommandBase* pCommandBase) = 0;
	virtual void UnregisterConCommands(CVarDLLIdentifier_t id) = 0;

	virtual const char* GetCommandLineValue(const char* pVariableName) = 0;

	virtual ConCommandBase* FindCommandBase(const char* name) = 0;
	virtual const ConCommandBase* FindCommandBase(const char* name) const = 0;
	virtual ConVar* FindVar(const char* var_name) = 0;
	virtual const ConVar* FindVar(const char* var_name) const = 0;
	virtual ConCommand* FindCommand(const char* name) = 0;
	virtual const ConCommand* FindCommand(const char* name) const = 0;

	virtual void sub_18000CF30() = 0;
	virtual void sub_18000E6F0() = 0;

	virtual void sub_18000C200() = 0;
	virtual void sub_18000E610() = 0;
	virtual void sub_180009DE0() = 0;

	virtual void sub_18000C190() = 0; // InstallConsoleDisplayFunc
	virtual void sub_18000E5A0() = 0; // RemoveConsoleDisplayFunc

	virtual void			ConsoleColorPrintf(const SourceColor& clr, const char* pFormat, ...) const;
	virtual void			ConsolePrintf(const char* pFormat, ...) const;
	virtual void			ConsoleDPrintf(const char* pFormat, ...) const;

	virtual void sub_18000EC50() = 0;

	virtual void sub_18000C170() = 0;

	virtual void sub_18000F4B0() = 0;
	virtual void sub_unk() = 0;
	virtual void sub_18000AEB0() = 0;
	virtual void sub_18000AEC0() = 0;
	virtual void sub_18000C530() = 0;
	virtual void sub_18000DD60() = 0;
	virtual void sub_18000DCD0() = 0;
	virtual void sub_18000DDF0() = 0;
	virtual void sub_18000B8A0() = 0;
	virtual void sub_18000D3C0() = 0;
	virtual void sub_18000A550() = 0;
/*
protected:
	class ICVarIteratorInternal
	{
	public:
		virtual void            SetFirst(void) = 0;
		virtual void            Next(void) = 0;
		virtual bool            IsValid(void) = 0;
		virtual ConCommandBase* Get(void) = 0;
	};

	virtual ICVarIteratorInternal* FactoryInternalIterator(void) = 0;
	*/
};
#endif
#endif // ICVAR_H
