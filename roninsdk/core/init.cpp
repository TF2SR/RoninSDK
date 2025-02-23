//=============================================================================//
//
// Purpose: Main systems initialization file
//
//=============================================================================//

#include "core/stdafx.h"
#include "core/logdef.h"
#include "tier0/fasttimer.h"
#include "tier1/strtools.h"
// Tier0
#include "tier0/platform_internal.h"
#include "tier0/memstd.h"
#include "tier0/commandline.h"
#include "launcher/IApplication.h"
#include "launcher/launcher.h"
#include "tier0/threadtools.h"
// Tier 1
#include "tier1/cmd.h"
#include "tier1/cvar.h"
// Engine
#include "engine/vgui_baseui_interface.h"
#include "engine/vengineserver_impl.h"
#include "engine/client/client.h"
#include "origin/originauth.h"
// Client
#include "gameui/GameConsoleDialog.h"
#include "vgui_controls/Panel.h"
#include "vgui_controls/Frame.h"
#include "vgui_controls/Label.h"
#include "vgui_controls/ListPanel.h"
#include "vgui_controls/EditablePanel.h"
#include "vgui_controls/BitmapImagePanel.h"
#include "vgui/vgui_fpspanel.h"
#include "vguimatsurface/MatSystemSurface.h"
// filesystem_stdio
#include "filesystem/basefilesystem.h"

// Squirrel
#include "squirrel/client/sqvm.h"
#include "squirrel/server/sqvm.h"
#include "squirrel/ui/sqvm.h"
#include "squirrel/client/sqscript.h"
#include "squirrel/server/sqscript.h"
#include "squirrel/client/sqapi.h"
#include "squirrel/server/sqapi.h"
#include "squirrel/ui/sqapi.h"
#include "squirrel/squirrelmanager.h"
#include "filesystem/diskvmtfixes.h"
#include "squirrel/sqfiles.h"
#include "speedrunning/modtimer.h"
#include "speedrunning/crouchkickfix.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// ██╗███╗   ██╗██╗████████╗██╗ █████╗ ██╗     ██╗███████╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
// ██║████╗  ██║██║╚══██╔══╝██║██╔══██╗██║     ██║╚══███╔╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
// ██║██╔██╗ ██║██║   ██║   ██║███████║██║     ██║  ███╔╝ ███████║   ██║   ██║██║   ██║██╔██╗ ██║
// ██║██║╚██╗██║██║   ██║   ██║██╔══██║██║     ██║ ███╔╝  ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
// ██║██║ ╚████║██║   ██║   ██║██║  ██║███████╗██║███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
// ╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝╚═╝  ╚═╝╚══════╝╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void Systems_Init()
{
	spdlog::info("+---------------------------------------------------------------------+");
	QuerySystemInfo();

	DetourRegister();
	//CFastTimer initTimer;

	//initTimer.Start();
	//DetourInit();
	//initTimer.End();

	spdlog::info("+---------------------------------------------------------------------+");
	REGISTER_MODULE("roninsdk.dll");
	REGISTER_MODULE("tier0.dll");
	REGISTER_MODULE("launcher.dll");
	//spdlog::info("{:16s} '{:10.6f}' seconds ('{:12d}' clocks)\n", "Detour->InitDB()", initTimer.GetDuration().GetSeconds(), initTimer.GetDuration().GetCycles());

	//initTimer.Start();

	// Begin the detour transaction to hook the process
	//DetourTransactionBegin();
	//DetourUpdateThread(GetCurrentThread());

	// Hook functions
	//for (const IDetour* pDetour : g_DetourVector)
	//{
	//	pDetour->Attach();
	//}

	// Patch instructions
	//RuntimePtc_Init();

	// Commit the transaction
	//HRESULT hr = DetourTransactionCommit();
	//if (hr != NO_ERROR)
	//{
	//	// Failed to hook into the process, terminate
	//	Error(eDLL_T::RONIN_GEN, 0xBAD0C0DE, "Failed to detour process: error code = %08x\n", hr);
	//}

	//initTimer.End();
	//spdlog::info("{:16s} '{:10.6f}' seconds ('{:12d}' clocks)\n", "Detour->Attach()", initTimer.GetDuration().GetSeconds(), initTimer.GetDuration().GetCycles());
	//spdlog::info("+---------------------------------------------------------------------+\n");

	//ConVar::StaticInit();
	g_pSQManager<ScriptContext::CLIENT> = new SquirrelManager<ScriptContext::CLIENT>;
	g_pSQManager<ScriptContext::SERVER> = new SquirrelManager<ScriptContext::SERVER>;
	g_pSQManager<ScriptContext::UI> = new SquirrelManager<ScriptContext::UI>;

	g_pSaveFileManager = new SaveFileManager;
}

//////////////////////////////////////////////////////////////////////////
//
// ███████╗██╗  ██╗██╗   ██╗████████╗██████╗  ██████╗ ██╗    ██╗███╗   ██╗
// ██╔════╝██║  ██║██║   ██║╚══██╔══╝██╔══██╗██╔═══██╗██║    ██║████╗  ██║
// ███████╗███████║██║   ██║   ██║   ██║  ██║██║   ██║██║ █╗ ██║██╔██╗ ██║
// ╚════██║██╔══██║██║   ██║   ██║   ██║  ██║██║   ██║██║███╗██║██║╚██╗██║
// ███████║██║  ██║╚██████╔╝   ██║   ██████╔╝╚██████╔╝╚███╔███╔╝██║ ╚████║
// ╚══════╝╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═════╝  ╚═════╝  ╚══╝╚══╝ ╚═╝  ╚═══╝
//
//////////////////////////////////////////////////////////////////////////

void Systems_Shutdown()
{
	CFastTimer shutdownTimer;
	shutdownTimer.Start();

	// Begin the detour transaction to unhook the process
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Unhook functions
	for (const pair<string, vector<IDetour*>> &Module : g_DetourMap)
	{
		for (const IDetour* pDetour : Module.second)
		{
			pDetour->Detach();
		}
	}

	// Commit the transaction
	DetourTransactionCommit();

	shutdownTimer.End();
	spdlog::info("{:16s} '{:10.6f}' seconds ('{:12d}' clocks)\n", "Detour->Detach()", shutdownTimer.GetDuration().GetSeconds(), shutdownTimer.GetDuration().GetCycles());
	spdlog::info("+---------------------------------------------------------------------+\n");
}

/////////////////////////////////////////////////////
//
// ██╗   ██╗████████╗██╗██╗     ██╗████████╗██╗   ██╗
// ██║   ██║╚══██╔══╝██║██║     ██║╚══██╔══╝╚██╗ ██╔╝
// ██║   ██║   ██║   ██║██║     ██║   ██║    ╚████╔╝ 
// ██║   ██║   ██║   ██║██║     ██║   ██║     ╚██╔╝  
// ╚██████╔╝   ██║   ██║███████╗██║   ██║      ██║   
//  ╚═════╝    ╚═╝   ╚═╝╚══════╝╚═╝   ╚═╝      ╚═╝   
//
/////////////////////////////////////////////////////

void Winsock_Init()
{
	/*
	WSAData wsaData{};
	int nError = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nError != 0)
	{
		Error(eDLL_T::RONIN_GEN, NO_ERROR, "%s: Failed to start Winsock: (%s)\n", __FUNCTION__, NET_ErrorString(WSAGetLastError()));
	}
	*/
}
void Winsock_Shutdown()
{
	/*
	int nError = ::WSACleanup();
	if (nError != 0)
	{
		Error(eDLL_T::RONIN_GEN, NO_ERROR, "%s: Failed to stop Winsock: (%s)\n", __FUNCTION__, NET_ErrorString(WSAGetLastError()));
	}
	*/
}
void QuerySystemInfo()
{
#ifndef DEDICATED
	for (int i = 0; ; i++)
	{
		DISPLAY_DEVICE dd = { sizeof(dd), {0} };
		BOOL f = EnumDisplayDevices(NULL, i, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
		if (!f)
		{
			break;
		}

		if (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) // Only log the primary device.
		{
			char szDeviceName[128];
#ifndef UNICODE
			strncpy_s(szDeviceName, dd.DeviceString, sizeof(szDeviceName));
#else
			wcstombs(szDeviceName, dd.DeviceString, sizeof(szDeviceName));
#endif // !UNICODE
			spdlog::info("{:25s}: '{:s}'", "GPU model identifier", szDeviceName);
		}
	}
#endif // !DEDICATED

	const CPUInformation& pi = GetCPUInformation();

	spdlog::info("{:25s}: '{:s}'", "CPU model identifier", pi.m_szProcessorBrand);
	spdlog::info("{:25s}: '{:s}'", "CPU vendor tag", pi.m_szProcessorID);
	spdlog::info("{:25s}: '{:12d}' ('{:2d}' {:s})", "CPU core count", pi.m_nPhysicalProcessors, pi.m_nLogicalProcessors, "logical");
	spdlog::info("{:25s}: '{:12d}' ({:12s})", "CPU core speed", pi.m_Speed, "Cycles");
	spdlog::info("{:20s}{:s}: '{:12d}' (0x{:<10X})", "L1 cache", "(KiB)", pi.m_nL1CacheSizeKb, pi.m_nL1CacheDesc);
	spdlog::info("{:20s}{:s}: '{:12d}' (0x{:<10X})", "L2 cache", "(KiB)", pi.m_nL2CacheSizeKb, pi.m_nL2CacheDesc);
	spdlog::info("{:20s}{:s}: '{:12d}' (0x{:<10X})", "L3 cache", "(KiB)", pi.m_nL3CacheSizeKb, pi.m_nL3CacheDesc);

	MEMORYSTATUSEX statex{};
	statex.dwLength = sizeof(statex);

	if (GlobalMemoryStatusEx(&statex))
	{
		DWORDLONG totalPhysical = (statex.ullTotalPhys / 1024) / 1024;
		DWORDLONG totalVirtual = (statex.ullTotalVirtual / 1024) / 1024;

		DWORDLONG availPhysical = (statex.ullAvailPhys / 1024) / 1024;
		DWORDLONG availVirtual = (statex.ullAvailVirtual / 1024) / 1024;

		spdlog::info("{:20s}{:s}: '{:12d}' ('{:9d}' {:s})", "Total system memory", "(MiB)", totalPhysical, totalVirtual, "virtual");
		spdlog::info("{:20s}{:s}: '{:12d}' ('{:9d}' {:s})", "Avail system memory", "(MiB)", availPhysical, availVirtual, "virtual");
	}
	else
	{
		spdlog::error("Unable to retrieve system memory information: {:s}\n",
			std::system_category().message(static_cast<int>(::GetLastError())));
	}
}

void CheckCPU() // Respawn's engine and our SDK utilize POPCNT, SSE3 and SSSE3 (Supplemental SSE 3 Instructions).
{
	const CPUInformation& pi = GetCPUInformation();
	static char szBuf[1024];
	if (!pi.m_bSSE3)
	{
		V_snprintf(szBuf, sizeof(szBuf), "CPU does not have %s!\n", "SSE 3");
		MessageBoxA(NULL, szBuf, "Unsupported CPU", MB_ICONERROR | MB_OK);
		ExitProcess(0xFFFFFFFF);
	}
	if (!pi.m_bSSSE3)
	{
		V_snprintf(szBuf, sizeof(szBuf), "CPU does not have %s!\n", "SSSE 3 (Supplemental SSE 3 Instructions)");
		MessageBoxA(NULL, szBuf, "Unsupported CPU", MB_ICONERROR | MB_OK);
		ExitProcess(0xFFFFFFFF);
	}
	if (!pi.m_bPOPCNT)
	{
		V_snprintf(szBuf, sizeof(szBuf), "CPU does not have %s!\n", "POPCNT");
		MessageBoxA(NULL, szBuf, "Unsupported CPU", MB_ICONERROR | MB_OK);
		ExitProcess(0xFFFFFFFF);
	}
}

bool AllocateModule(string strModule)
{
	SCAN_MODULE(strModule, roninsdk.dll, g_pSDKDll);
	SCAN_MODULE(strModule, tier0.dll, g_pTier0Dll);
	SCAN_MODULE(strModule, launcher.dll, g_pLauncherDll);
	SCAN_MODULE(strModule, engine.dll, g_pEngineDll);
	SCAN_MODULE(strModule, client.dll, g_pClientDll);
	SCAN_MODULE(strModule, server.dll, g_pServerDll);
	SCAN_MODULE(strModule, filesystem_stdio.dll, g_pFSStdioDll);
	SCAN_MODULE(strModule, materialsystem_dx11.dll, g_pMatSys_DX11Dll);
	SCAN_MODULE(strModule, inputsystem.dll, g_pInputSystemDll);

	return false;
}

void DetourScanModule(string strModule)
{
	bool bLogAdr = g_svCmdLine.find("-sig_toconsole") != string::npos;
	bool bInitDivider = false;

	CFastTimer scanTimer;
	scanTimer.Start();

	for (const IDetour* pDetour : g_DetourMap[strModule])
	{
		pDetour->GetCon(); // Constants.
		pDetour->GetFun(); // Functions.
		pDetour->GetVar(); // Variables.

		if (bLogAdr)
		{
			if (!bInitDivider)
			{
				bInitDivider = true;
				spdlog::debug("+---------------------------------------------------------------------+\n");
			}
			pDetour->GetAdr();
			spdlog::debug("+---------------------------------------------------------------------+\n");
		}
	}

	scanTimer.End();
	DevMsg(eDLL_T::RONIN_GEN, "Scanning '%s' took '%f' seconds", strModule.c_str(), scanTimer.GetDuration().GetSeconds());
}

void DetourAttachModule(string strModule)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	for (const IDetour* pDetour : g_DetourMap[strModule])
	{
		pDetour->Attach();
	}

	DetourTransactionCommit();
}

void DetourAddress()
{
	spdlog::debug("+---------------------------------------------------------------------+\n");
	for (const pair<string, vector<IDetour*>>& Module : g_DetourMap)
	{
		for (const IDetour* pDetour : Module.second)
		{
			pDetour->GetAdr();
			spdlog::debug("+---------------------------------------------------------------------+\n");
		}
	}
}

void DetourRegister() // Register detour classes to be searched and hooked.
{
	// Launcher
	REGISTER(launcher.dll, VLauncher);

	// Tier0
	REGISTER(tier0.dll, VPlatform);
	REGISTER(tier0.dll, VMemStd);
	REGISTER(tier0.dll, VCommandLine);
	REGISTER(tier0.dll, VThreadTools);

	// Tier1
	REGISTER(engine.dll, VConCommand);
	REGISTER(engine.dll, VConVar);
	REGISTER(engine.dll, VApplication);
	REGISTER(engine.dll, VEngineVgui);

	REGISTER(engine.dll, VEngineServer);
	REGISTER(engine.dll, VClient);
	REGISTER(engine.dll, VOrigin);

	// Client
	REGISTER(client.dll, VConsoleDialog);
	REGISTER(client.dll, VguiFrame);
	REGISTER(client.dll, VguiPanel);
	REGISTER(client.dll, VguiLabel);
	REGISTER(client.dll, VguiListPanel);
	REGISTER(client.dll, VguiEditablePanel);
	REGISTER(client.dll, VCBitmapImagePanel);
	REGISTER(client.dll, VFPSPanel);
	REGISTER(client.dll, VMatSystemSurface);

	// Filesystem
	REGISTER(filesystem_stdio.dll, VBaseFileSystem);

	// Squirrel
	REGISTER(client.dll, HSQVM_CLIENT);
	REGISTER(server.dll, HSQVM_SERVER);
	REGISTER(client.dll, HSQVM_UI);
	REGISTER(client.dll, VSQVM_CLIENT);
	REGISTER(server.dll, VSQVM_SERVER);
	REGISTER(client.dll, VSqapi_CLIENT);
	REGISTER(server.dll, VSqapi_SERVER);
	REGISTER(client.dll, VSqapi_UI);

	// disk vmt fix
	REGISTER(materialsystem_dx11.dll, VDiskVMTFixes);

	// timer
	REGISTER(client.dll, VModTimerClient);
	REGISTER(engine.dll, VModTimerEngine);
	REGISTER(server.dll, VModTimerServer);

	// CKF
	REGISTER(inputsystem.dll, VInputSystemHooksCKF);
	REGISTER(engine.dll, VEngineHooksCKF);
}