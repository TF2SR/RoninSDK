#pragma once

#include "filesystem.h"
#include "ipackedstore.h"

const std::string MOD_FILE_DIR = "ronin\\";

inline CMemory p_CBaseFileSystem__ReadFileFromVPK;
inline auto v_CBaseFileSystem__ReadFileFromVPK = p_CBaseFileSystem__ReadFileFromVPK.RCast<FileHandle_t(*)(void *self, FileHandle_t pResult, char* pszFilePath)>();

inline CMemory p_CBaseFileSystem__LoadFromCache;
inline auto v_CBaseFileSystem__LoadFromCache = p_CBaseFileSystem__LoadFromCache.RCast<bool(*)(void* self, char* pszFilePath, void* pResult)>();

inline CMemory p_CBaseFileSystem__MountVPKFile;
inline auto v_CBaseFileSystem__MountVPKFile = p_CBaseFileSystem__MountVPKFile.RCast<VPKData_t*(*)(void* self, const char* pszVpkPath)>();

inline CMemory p_CBaseFileSystem__UnmountVPKFile;
inline auto v_CBaseFileSystem__UnmountVPKFile = p_CBaseFileSystem__UnmountVPKFile.RCast<const char*(*)(void* self, const char* pszVpkPath)>();

inline CMemory p_CBaseFileSystem__GetMountedVPKHandle;
inline auto v_CBaseFileSystem__GetMountedVPKHandle = p_CBaseFileSystem__GetMountedVPKHandle.RCast<int(*)(void* self, const char* pszVpkPath)>();

inline CMemory p_CBaseFileSystem__AddSearchPath;
inline auto v_CBaseFileSystem__AddSearchPath = p_CBaseFileSystem__AddSearchPath.RCast<void(*)(IFileSystem* self, const char* pPath, const char* pathID, SearchPathAdd_t addType)>();

inline CMemory p_CBaseFileSystem__OpenEx;
inline auto v_CBaseFileSystem__OpenEx = p_CBaseFileSystem__OpenEx.RCast<FileHandle_t(*)(IFileSystem * filesystem, const char* pPath, const char* pOptions, uint32_t flags, const char* pPathID, char** ppszResolvedFilename)>();

///////////////////////////////////////////////////////////////////////////////
class VBaseFileSystem : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CBaseFileSystem::ReadFileFromVPK", p_CBaseFileSystem__ReadFileFromVPK.GetPtr());
		LogFunAdr("CBaseFileSystem::LoadFromCache", p_CBaseFileSystem__LoadFromCache.GetPtr());
		LogFunAdr("CBaseFileSystem::MountVPKFile", p_CBaseFileSystem__MountVPKFile.GetPtr());
		LogFunAdr("CBaseFileSystem::UnmountVPKFile", p_CBaseFileSystem__UnmountVPKFile.GetPtr());
		LogFunAdr("CBaseFileSystem::GetMountedVPKHandle", p_CBaseFileSystem__GetMountedVPKHandle.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CBaseFileSystem__ReadFileFromVPK = g_pFSStdioDll->Offset(0x5CBA0); /* "48 89 5C 24 08 57 48 81 EC C0" */
		v_CBaseFileSystem__ReadFileFromVPK = p_CBaseFileSystem__ReadFileFromVPK.RCast<FileHandle_t(*)(void* self, FileHandle_t pResult, char* pszFilePath)>();

		p_CBaseFileSystem__LoadFromCache = g_pFSStdioDll->Offset(0xFE50); /* "40 53 48 81 EC 40 02 00" */
		v_CBaseFileSystem__LoadFromCache = p_CBaseFileSystem__LoadFromCache.RCast<bool(*)(void* self, char* pszFilePath, void* pResult)>();

		p_CBaseFileSystem__MountVPKFile = g_pFSStdioDll->Offset(0xBEA0); /* "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 81 EC 50 02 00 00 48 8B" */
		v_CBaseFileSystem__MountVPKFile = p_CBaseFileSystem__MountVPKFile.RCast<VPKData_t*(*)(void* self, const char* pszVpkPath)>();

		p_CBaseFileSystem__UnmountVPKFile = g_pFSStdioDll->Offset(0x1A120); /* "48 89 5C 24 08 57 48 83  EC 20 48 8B DA 48 8B F9 48 8D" */
		v_CBaseFileSystem__UnmountVPKFile = p_CBaseFileSystem__UnmountVPKFile.RCast<const char*(*)(void* self, const char* pszVpkPath)>();

		p_CBaseFileSystem__GetMountedVPKHandle = g_pFSStdioDll->Offset(0x10AB0); /* "40 53 48 83 EC 20 48 8B D9 E8 F2 0C 00 00 85 C0" */
		v_CBaseFileSystem__GetMountedVPKHandle = p_CBaseFileSystem__GetMountedVPKHandle.RCast<int(*)(void* self, const char* pszVpkPath)>();

		p_CBaseFileSystem__AddSearchPath = g_pFSStdioDll->Offset(0xB510);
		v_CBaseFileSystem__AddSearchPath = p_CBaseFileSystem__AddSearchPath.RCast<void(*)(IFileSystem * self, const char* pPath, const char* pathID, SearchPathAdd_t addType)>();

		p_CBaseFileSystem__OpenEx = g_pFSStdioDll->Offset(0x15F50);
		v_CBaseFileSystem__OpenEx = p_CBaseFileSystem__OpenEx.RCast<FileHandle_t(*)(IFileSystem * filesystem, const char* pPath, const char* pOptions, uint32_t flags, const char* pPathID, char** ppszResolvedFilename)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};