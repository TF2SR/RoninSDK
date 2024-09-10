//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $NoKeywords: $
//===========================================================================//

#ifndef CVAR_H
#define CVAR_H

#include "icvar.h"
#include "public/tier1/cmd.h"

///////////////////////////////////////////////////////////////////////////////
extern ICvar* g_pCVar;

#if 1

//-----------------------------------------------------------------------------
// ENGINE                                                                     |

//-------------------------------------------------------------------------
// CLIENT                                                                 |
extern ConVar* cl_showsdkdbg;

//#include "vstdlib/concommandhash.h"

//-------------------------------------------------------------------------
// ENGINE                                                                 |
//extern ConVar* sdk_fixedframe_tickinterval;

/* ==== CCVAR =========================================================================================================================================================== */

/*
class CCvar
{ 	// Implementation in engine.
protected:
	enum ConVarSetType_t
	{
		CONVAR_SET_STRING = 0,
		CONVAR_SET_INT,
		CONVAR_SET_FLOAT,
	};

	struct QueuedConVarSet_t
	{
		ConVar* m_pConVar;
		ConVarSetType_t m_nType;
		int m_nInt;
		float m_flFloat;
		CUtlString m_String;
	};

	class CCVarIteratorInternal : public ICVarIteratorInternal
	{
	public:
		virtual void            SetFirst(void) = 0; //0
		virtual void            Next(void) = 0; //1
		virtual	bool            IsValid(void) = 0; //2
		virtual ConCommandBase* Get(void) = 0; //3

		CCvar* const m_pOuter = nullptr;
		CConCommandHash* const m_pHash = nullptr;
		CConCommandHash::CCommandHashIterator_t m_hashIter;
	};

	virtual CCVarIteratorInternal* FactoryInternalIterator(void) = 0;

	friend class CCVarIteratorInternal;
	friend class CCvarUtilities;

private:
	CUtlVector< FnChangeCallback_t > m_GlobalChangeCallbacks;
	char pad0[30];           //!TODO:
	int m_nNextDLLIdentifier;
	ConCommandBase* m_pConCommandList;
	CConCommandHash m_CommandHash;
	CUtlVector<void*> m_Unknown;
	char pad2[32];
	void* m_pCallbackStub;
	void* m_pAllocFunc;
	char pad3[16];
	CUtlVector< QueuedConVarSet_t > m_QueuedConVarSets;
	bool m_bMaterialSystemThreadSetAllowed;
};
*/

/* ==== CONVAR ========================================================================================================================================================== */
//-----------------------------------------------------------------------------
// Purpose: A console variable
//-----------------------------------------------------------------------------
class ConVar : public ConCommandBase//, public IConVar
{
public:
	static ConVar* StaticCreate(const char* pszName, const char* pszDefaultValue, int nFlags, const char* pszHelpString,
		bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t pCallback);

	static void StaticInit(void);
	static void InitShipped(void);
	static void PurgeShipped(void);

	const char* GetBaseName(void) const;
	const char* GetHelpText(void) const;

	void AddFlags(int nFlags);
	void RemoveFlags(int nFlags);

	bool GetBool(void) const;
	float GetFloat(void) const;
	int GetInt(void) const;
	Color GetColor(void) const;
	const char* GetString(void) const;

	bool GetMin(float& flMinValue) const;
	bool GetMax(float& flMaxValue) const;
	float GetMinValue(void) const;
	float GetMaxValue(void) const;

	bool HasMin(void) const;
	bool HasMax(void) const;

	void SetValue(int nValue);
	void SetValue(float flValue);
	void SetValue(const char* pszValue);
	void SetValue(Color clValue);

	void ChangeStringValue(const char* pszTempValue, float flOldValue);
	bool SetColorFromString(const char* pszValue);
	bool ClampValue(float& value);

	bool IsRegistered(void) const;
	bool IsCommand(void) const;
	bool IsFlagSet(int nFlags) const;

	struct CVValue_t
	{
		const char* m_pszString;
		int64_t m_iStringLength;
		float m_fValue;
		int m_nValue;
	};

	//ConCommandBase m_ConCommandBase{}; // 0x0000
	const char* m_pszDefaultValue{}; // 0x0040
	CVValue_t m_Value{}; // 0x0048
	bool m_bHasMin{}; // 0x005C
	float m_fMinVal{}; // 0x0060
	bool m_bHasMax{}; // 0x0064
	float m_fMaxVal{}; // 0x0068
	void* m_pMalloc{}; // 0x0070
	char m_pPad80[10]{}; // 0x0080
}; //Size: 0x0080
//static_assert(sizeof(ConVar) == 0x90);

///////////////////////////////////////////////////////////////////////////////
void ConVar_PrintDescription(ConCommandBase* pVar);

/* ==== CONVAR ========================================================================================================================================================== */
inline CMemory p_ConVar_ConVar;
inline auto v_ConVar_ConVar = p_ConVar_ConVar.RCast<void(*)(ConVar * pConVar,
	const char* pszName,
	const char* pszDefaultValue,
	int nFlags,
	const char* pszHelpString,
	bool bMin,
	float fMin,
	bool bMax,
	float fMax,
	FnChangeCallback_t pCallback)>();

inline CMemory p_ConVar_Malloc;
inline auto v_ConVar_Malloc = p_ConVar_Malloc.RCast<void(*)(void* pConVarMaloc, int a2, int a3)>();

inline ConVar* g_pConVarVBTable;
inline IConVar* g_pConVarVFTable;

///////////////////////////////////////////////////////////////////////////////
class VConVar : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("ConVar::ConVar", p_ConVar_ConVar.GetPtr());
		LogFunAdr("ConVar::Malloc", p_ConVar_Malloc.GetPtr());
		LogConAdr("ConVar::`vbtable'", reinterpret_cast<uintptr_t>(g_pConVarVBTable));
		LogConAdr("ConVar::`vftable'", reinterpret_cast<uintptr_t>(g_pConVarVFTable));
	}
	virtual void GetFun(void) const
	{
		p_ConVar_ConVar = g_pEngineDll->Offset(0x417230); /* "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 F3" */
		v_ConVar_ConVar = p_ConVar_ConVar.RCast<void(*)(ConVar*, const char*, const char*, int, const char*, bool, float, bool, float, FnChangeCallback_t)>();

		/* 48 89 5C 24 08 57 48 83 EC 20 49 63 F8 48 63 C2 48 8B D9 48 C7 01 00 00 00 00 48 89 79 08 48 89 41 10 45 85 C0 74 4C 48 8B 0D 6A 91 1A 00 48 C1 */
		p_ConVar_Malloc = g_pEngineDll->Offset(0x415C20);
		v_ConVar_Malloc = p_ConVar_Malloc.RCast<void(*)(void* pConVarMaloc, int a2, int a3)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const
	{
		g_pConVarVBTable = g_pEngineDll->GetVirtualMethodTable(".?AVConVar@@").RCast<ConVar*>();
		g_pConVarVFTable = g_pEngineDll->GetVirtualMethodTable(".?AVConVar@@").Offset(0xA0).RCast<IConVar*>();
	}
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////
#endif 
#endif // CVAR_H
