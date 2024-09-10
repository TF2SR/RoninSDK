#ifndef LAUNCHER_H
#define LAUNCHER_H

inline CMemory p_LauncherMain;
inline auto v_LauncherMain = p_LauncherMain.RCast<int(*)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)>();

// CSourceAppSystemGroup table : 0x180065798
inline CMemory p_CSourceAppSystemGroup__PreInit;
inline auto v_CSourceAppSystemGroup__PreInit = p_CSourceAppSystemGroup__PreInit.RCast<bool(*)(void* pModAppSystemGroup)>();

inline CMemory p_CSourceAppSystemGroup__Create;
inline auto v_CSourceAppSystemGroup__Create = p_CSourceAppSystemGroup__Create.RCast<bool(*)(void* pModAppSystemGroup)>();

///////////////////////////////////////////////////////////////////////////////
class VLauncher : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("LauncherMain", p_LauncherMain.GetPtr());
		LogFunAdr("CSourceAppSystemGroup::PreInit", p_CSourceAppSystemGroup__PreInit.GetPtr());
		LogFunAdr("CSourceAppSystemGroup::Create", p_CSourceAppSystemGroup__Create.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_LauncherMain = g_pLauncherDll->GetExportedFunction("LauncherMain");
		v_LauncherMain = p_LauncherMain.RCast<int(*)(HINSTANCE, HINSTANCE, LPSTR, int)>();

		p_CSourceAppSystemGroup__PreInit = g_pLauncherDll->Offset(0xB730); /* "48 89 7C 24 18 55 48 8D AC 24 90 FA FF FF 48" */
		v_CSourceAppSystemGroup__PreInit = p_CSourceAppSystemGroup__PreInit.RCast<bool(*)(void*)>();

		p_CSourceAppSystemGroup__Create = g_pLauncherDll->Offset(0x94E0); /* "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 55 48" */
		v_CSourceAppSystemGroup__Create = p_CSourceAppSystemGroup__Create.RCast<bool(*)(void*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};
///////////////////////////////////////////////////////////////////////////////

#endif // LAUNCHER_H