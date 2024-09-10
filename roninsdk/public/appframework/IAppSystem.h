//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: An application framework 
//
// $Revision: $
// $NoKeywords: $
//===========================================================================//

#ifndef IAPPSYSTEM_H
#define IAPPSYSTEM_H

#include "tier1/interface.h"

//-----------------------------------------------------------------------------
// Specifies a module + interface name for initialization
//-----------------------------------------------------------------------------
struct AppSystemInfo_t
{
	const char* m_pModuleName;
	const char* m_pInterfaceName;
};

//-----------------------------------------------------------------------------
// Client systems are singleton objects in the client codebase responsible for
// various tasks
// The order in which the client systems appear in this list are the
// order in which they are initialized and updated. They are shut down in
// reverse order from which they are initialized.
//-----------------------------------------------------------------------------
enum InitReturnVal_t
{
	INIT_FAILED = 0,
	INIT_OK,

	INIT_LAST_VAL,
};

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
enum AppSystemTier_t
{
	APP_SYSTEM_TIER0 = 0,
	APP_SYSTEM_TIER1,
	APP_SYSTEM_TIER2,
	APP_SYSTEM_TIER3,

	APP_SYSTEM_TIER_OTHER,
};

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
/*
.rdata:000000018005B0C8 ??_7IAppSystem@@6B@ dq offset sub_180009910
.rdata:000000018005B0C8                                         ; DATA XREF: .text:0000000180008C80↑o
.rdata:000000018005B0C8                                         ; .text:0000000180008D00↑o ...
.rdata:000000018005B0D0                 dq offset _purecall
.rdata:000000018005B0D8                 dq offset _purecall
.rdata:000000018005B0E0                 dq offset _purecall
.rdata:000000018005B0E8                 dq offset _purecall
.rdata:000000018005B0F0                 dq offset _purecall
.rdata:000000018005B0F8                 dq offset _purecall
.rdata:000000018005B100                 dq offset _purecall
*/
abstract_class IAppSystem
{
public:
	virtual ~IAppSystem() = 0; // Prepended on each class derived class in assembly.

	// Here's where the app systems get to learn about each other 
	virtual bool Connect(CreateInterfaceFn factory) = 0;
	virtual void Disconnect() = 0;

	// Here's where systems can access other interfaces implemented by this object
	// Returns NULL if it doesn't implement the requested interface
	virtual void* QueryInterface(const char* pInterfaceName) = 0;

	// Init, shutdown
	virtual InitReturnVal_t Init() = 0;
	virtual void Shutdown() = 0;

	// Returns all dependent libraries
	virtual const AppSystemInfo_t* GetDependencies() = 0;

	// Returns the tier
	//virtual AppSystemTier_t GetTier() = 0;

	// Reconnect to a particular interface
	virtual void Reconnect(CreateInterfaceFn factory, const char* pInterfaceName) = 0;
};
#if 0
//-----------------------------------------------------------------------------
// Helper empty implementation of an IAppSystem
//-----------------------------------------------------------------------------
template< class IInterface >
class CBaseAppSystem : public IInterface
{
public:
	virtual ~CBaseAppSystem() = 0; // Prepended on each class derived class in assembly.

	// Here's where the app systems get to learn about each other 
	virtual bool Connect(CreateInterfaceFn factory) = 0;
	virtual void Disconnect() = 0;

	// Here's where systems can access other interfaces implemented by this object
	// Returns NULL if it doesn't implement the requested interface
	virtual void* QueryInterface(const char* pInterfaceName) = 0;

	// Init, shutdown
	virtual InitReturnVal_t Init() = 0;
	virtual void Shutdown() = 0;

	// Returns all dependent libraries
	//virtual const AppSystemInfo_t* GetDependencies() { return NULL; }

	// Returns the tier
	virtual AppSystemTier_t GetTier() = 0;

	// Reconnect to a particular interface
	virtual void Reconnect(CreateInterfaceFn factory, const char* pInterfaceName) = 0;
};
#endif
#endif // IAPPSYSTEM_H