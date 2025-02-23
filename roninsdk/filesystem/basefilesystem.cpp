#include "basefilesystem.h"

#define MOD_FILE_DIR "ronin\\"

void CBaseFileSystem__AddSearchPath(IFileSystem* self, const char* pPath, const char* pathID, SearchPathAdd_t addType)
{
	// DevMsg(eDLL_T::FS, "AddSearchPath %s %s %i\n", pPath, pathID, addType);
	v_CBaseFileSystem__AddSearchPath(self, pPath, pathID, addType);

	std::string modFileDir = MOD_FILE_DIR;
	if (!strcmp(pathID, "GAME") && modFileDir.compare(pPath) && addType == SearchPathAdd_t::PATH_ADD_TO_HEAD)
	{
		DevMsg(eDLL_T::FS, "Adding mod path in...\n", pPath, pathID, addType);
		char dir[MAX_PATH];
		if (!g_pFullFileSystem->GetCurrentDirectory(dir, MAX_PATH))
			return;
		std::string dirStr = dir;
		dirStr += "\\";
		dirStr += MOD_FILE_DIR;
		v_CBaseFileSystem__AddSearchPath(self, dirStr.c_str(), "GAME", SearchPathAdd_t::PATH_ADD_TO_HEAD);
	}
}

bool CBaseFilesystem__VCheckDisk(const char* pszFilePath)
{
	std::string svFilePath = ConvertToWinPath(pszFilePath);
	if (svFilePath.find("\\*\\") != string::npos)
	{
		// Erase '//*/'.
		svFilePath.erase(0, 4);
	}

	fs::path filePath(svFilePath);
	if (filePath.is_absolute())
	{
		// Skip absolute file paths.
		return false;
	}

	// TODO: obtain 'mod' SearchPath's instead.
	svFilePath.insert(0, MOD_FILE_DIR);

	if (::FileExists(svFilePath) /*|| ::FileExists(pszFilePath)*/)
	{
		char dir[MAX_PATH];
		if (!g_pFullFileSystem->GetCurrentDirectory(dir, MAX_PATH))
			return false;
		std::string dirStr = dir;
		dirStr += "\\";
		dirStr += MOD_FILE_DIR;

		v_CBaseFileSystem__AddSearchPath(g_pFullFileSystem, dirStr.c_str(), "GAME", SearchPathAdd_t::PATH_ADD_TO_HEAD);

		return true;
	}

	return false;
}


FileHandle_t CBaseFileSystem__ReadFileFromVPK(void* self, FileHandle_t pResult, char* pszFilePath)
{
	//DevMsg(eDLL_T::FS, "ReadFileFromVPK: %s\n", pszFilePath);

	if (CBaseFilesystem__VCheckDisk(pszFilePath))
	{
		*reinterpret_cast<int64_t*>(pResult) = -1;
		return pResult;
	}

	return v_CBaseFileSystem__ReadFileFromVPK(self, pResult, pszFilePath);
}

bool CBaseFileSystem__LoadFromCache(void* self, char* pszFilePath, void* pResult)
{
	//DevMsg(eDLL_T::FS, "LoadFromCache: %s\n", pszFilePath);

	// Invalidate cache entry if the file exists on disk
	// so we can then redirect to it in ReadFileFromVPK
	if (CBaseFilesystem__VCheckDisk(pszFilePath))
	{
		return false;
	}

	return v_CBaseFileSystem__LoadFromCache(self, pszFilePath, pResult);
}

VPKData_t* CBaseFileSystem__MountVPKFile(void* self, const char* pszVpkPath)
{
	int nHandle = v_CBaseFileSystem__GetMountedVPKHandle(self, pszVpkPath);
	VPKData_t* pData = v_CBaseFileSystem__MountVPKFile(self, pszVpkPath);

	if (pData)
	{
		if (nHandle < 0) // Only log if vpk hasn't been mounted yet...
		{
			DevMsg(eDLL_T::FS, "Mounted VPK file: '%s' with handle: '%i'\n", pszVpkPath, pData->m_nHandle);
		}
	}
	else
	{
		Warning(eDLL_T::FS, "Unable to mount VPK file: '%s'\n", pszVpkPath);
	}

	if (pszVpkPath != "vpk/client_mp_common.bsp")
		v_CBaseFileSystem__MountVPKFile(self, "vpk/client_mp_common.bsp");

	return pData;
}

const char* CBaseFileSystem__UnmountVPKFile(void* self, const char* pszVpkPath)
{
	int nHandle = v_CBaseFileSystem__GetMountedVPKHandle(self, pszVpkPath);
	const char* pRet = v_CBaseFileSystem__UnmountVPKFile(self, pszVpkPath);

	if (nHandle >= 0)
	{
		//DevMsg(eDLL_T::FS, "Unmounted VPK file: '%s' with handle: '%i'\n", pszVpkPath, nHandle);
	}

	return pRet;
}

FileHandle_t CBaseFileSystem__OpenEx(IFileSystem* filesystem, const char* pPath, const char* pOptions, uint32_t flags, const char* pPathID, char** ppszResolvedFilename)
{
	CBaseFilesystem__VCheckDisk(pPath);
	return v_CBaseFileSystem__OpenEx(filesystem, pPath, pOptions, flags, pPathID, ppszResolvedFilename);
}

void VBaseFileSystem::Attach() const
{
	DetourAttach((LPVOID*)&v_CBaseFileSystem__ReadFileFromVPK, &CBaseFileSystem__ReadFileFromVPK);
	DetourAttach((LPVOID*)&v_CBaseFileSystem__LoadFromCache, &CBaseFileSystem__LoadFromCache);
	DetourAttach((LPVOID*)&v_CBaseFileSystem__MountVPKFile, &CBaseFileSystem__MountVPKFile);
	DetourAttach((LPVOID*)&v_CBaseFileSystem__UnmountVPKFile, &CBaseFileSystem__UnmountVPKFile);
	DetourAttach((LPVOID*)&v_CBaseFileSystem__AddSearchPath, &CBaseFileSystem__AddSearchPath);
	DetourAttach((LPVOID*)&v_CBaseFileSystem__OpenEx, &CBaseFileSystem__OpenEx);
}
void VBaseFileSystem::Detach() const
{
	DetourDetach((LPVOID*)&v_CBaseFileSystem__ReadFileFromVPK, &CBaseFileSystem__ReadFileFromVPK);
	DetourDetach((LPVOID*)&v_CBaseFileSystem__LoadFromCache, &CBaseFileSystem__LoadFromCache);
	DetourDetach((LPVOID*)&v_CBaseFileSystem__MountVPKFile, &CBaseFileSystem__MountVPKFile);
	DetourAttach((LPVOID*)&v_CBaseFileSystem__UnmountVPKFile, &CBaseFileSystem__UnmountVPKFile);
	DetourDetach((LPVOID*)&v_CBaseFileSystem__AddSearchPath, &CBaseFileSystem__AddSearchPath);
	DetourDetach((LPVOID*)&v_CBaseFileSystem__OpenEx, &CBaseFileSystem__OpenEx);
}