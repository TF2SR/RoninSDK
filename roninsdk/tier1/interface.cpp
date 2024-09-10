#include "tier1/interface.h"

CMemory Sys_GetFactoryPtr(const string& svModuleName, const string& svFactoryName)
{
	HMODULE hModule = GetModuleHandleA(svModuleName.c_str());

	if (!hModule)
		Error(eDLL_T::COMMON, 0xBAD0C0DE, "Failed to get module handle of '%s'!\n", svModuleName.c_str());

	CreateInterfaceFn fnCreateInterface = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(hModule, CREATEINTERFACE_PROCNAME));

	return fnCreateInterface(svFactoryName.c_str(), NULL);
}