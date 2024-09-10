#include "core/logdef.h"
#include "launcher/launcher.h"
#include "tier1/cmd.h"
#include "tier1/cvar.h"

int LauncherMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DevMsg(eDLL_T::NONE, "LauncherMain\n");
	return v_LauncherMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}

bool CSourceAppSystemGroup__PreInit(void* pModAppSystemGroup)
{
	DevMsg(eDLL_T::NONE, "CSourceAppSystemGroup__PreInit\n");

	// [Fifty]: r5r has a check for 'CSourceAppSystemGroup::CREATION' here
	// i dont know how the inheritance do so i just added a defensive check
	static bool bCalled = false;

	if (bCalled)
		Error(eDLL_T::NONE, 0xAAAAAAAA, "CSourceAppSystemGroup__PreInit called more than once!");

	bCalled = true;

	//Sleep(5000);

	ConCommand::StaticInit();
	ConVar::StaticInit();

	return v_CSourceAppSystemGroup__PreInit(pModAppSystemGroup);
}

bool CSourceAppSystemGroup__Create(void* pModAppSystemGroup)
{
	DevMsg(eDLL_T::NONE, "CSourceAppSystemGroup__Create\n");
	return v_CSourceAppSystemGroup__Create(pModAppSystemGroup);
}

void VLauncher::Attach(void) const
{
	DetourAttach((LPVOID*)&v_LauncherMain, &LauncherMain);
	DetourAttach((LPVOID*)&v_CSourceAppSystemGroup__PreInit, &CSourceAppSystemGroup__PreInit);
	DetourAttach((LPVOID*)&v_CSourceAppSystemGroup__Create, &CSourceAppSystemGroup__Create);
}

void VLauncher::Detach(void) const
{
	DetourDetach((LPVOID*)&v_LauncherMain, &LauncherMain);
	DetourDetach((LPVOID*)&v_CSourceAppSystemGroup__PreInit, &CSourceAppSystemGroup__PreInit);
	DetourDetach((LPVOID*)&v_CSourceAppSystemGroup__Create, &CSourceAppSystemGroup__Create);
}