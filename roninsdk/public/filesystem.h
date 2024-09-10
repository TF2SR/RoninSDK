#pragma once

#include "appframework/IAppSystem.h"

typedef void* FileHandle_t;

//-----------------------------------------------------------------------------
// File system allocation functions. Client must free on failure
//-----------------------------------------------------------------------------
typedef void* (*FSAllocFunc_t)(const char* pszFilename, unsigned nBytes);

enum class SearchPathAdd_t : int
{
	PATH_ADD_TO_HEAD,         // First path searched
	PATH_ADD_TO_TAIL,         // Last path searched
	PATH_ADD_TO_TAIL_ATINDEX, // First path searched
};

enum class FileWarningLevel_t : int
{
	FILESYSTEM_WARNING = -1,                        // A problem!
	FILESYSTEM_WARNING_QUIET = 0,                   // Don't print anything
	FILESYSTEM_WARNING_REPORTUNCLOSED,              // On shutdown, report names of files left unclosed
	FILESYSTEM_WARNING_REPORTUSAGE,                 // Report number of times a file was opened, closed
	FILESYSTEM_WARNING_REPORTALLACCESSES,           // Report all open/close events to console ( !slow! )
	FILESYSTEM_WARNING_REPORTALLACCESSES_READ,      // Report all open/close/read events to the console ( !slower! )
	FILESYSTEM_WARNING_REPORTALLACCESSES_READWRITE, // Report all open/close/read/write events to the console ( !slower! )
	FILESYSTEM_WARNING_REPORTALLACCESSES_ASYNC      // Report all open/close/read/write events and all async I/O file events to the console ( !slower(est)! )
};

#define FILESYSTEM_MAX_SEARCH_PATHS 128

enum FileMode_t
{
	FM_BINARY,
	FM_TEXT
};

enum FileType_t
{
	FT_NORMAL,
	FT_PACK_BINARY,
	FT_PACK_TEXT,
	FT_MEMORY_BINARY,
	FT_MEMORY_TEXT
};

enum FileSystemSeek_t
{
	FILESYSTEM_SEEK_HEAD = SEEK_SET,
	FILESYSTEM_SEEK_CURRENT = SEEK_CUR,
	FILESYSTEM_SEEK_TAIL = SEEK_END,
};

enum
{
	FILESYSTEM_INVALID_FIND_HANDLE = -1
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

#define BASEFILESYSTEM_INTERFACE_VERSION		"VBaseFileSystem011"

abstract_class IBaseFileSystem
{
public:
	/*
	virtual int				Read(void* pOutput, int size, FileHandle_t file) = 0;
	virtual int				Write(void const* pInput, int size, FileHandle_t file) = 0;

	// if pathID is NULL, all paths will be searched for the file
	virtual FileHandle_t	Open(const char* pFileName, const char* pOptions, const char* pathID = 0) = 0;
	virtual void			Close(FileHandle_t file) = 0;


	virtual void			Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType) = 0;
	virtual unsigned int	Tell(FileHandle_t file) = 0;
	virtual unsigned int	Size(FileHandle_t file) = 0;
	virtual unsigned int	Size(const char* pFileName, const char* pPathID = 0) = 0;

	virtual void			Flush(FileHandle_t file) = 0;
	virtual bool			Precache(const char* pFileName, const char* pPathID = 0) = 0;

	virtual bool			FileExists(const char* pFileName, const char* pPathID = 0) = 0;
	virtual bool			IsFileWritable(char const* pFileName, const char* pPathID = 0) = 0;
	virtual bool			SetFileWritable(char const* pFileName, bool writable, const char* pPathID = 0) = 0;

	virtual time_t			GetFileTime(const char* pFileName, const char* pPathID = 0) = 0;

	//--------------------------------------------------------
	// Reads/writes files to utlbuffers. Use this for optimal read performance when doing open/read/close
	//--------------------------------------------------------
	virtual bool			ReadFile(const char* pFileName, const char* pPath, CUtlBuffer& buf, int nMaxBytes = 0, int nStartingByte = 0, FSAllocFunc_t pfnAlloc = NULL) = 0;
	virtual bool			WriteFile(const char* pFileName, const char* pPath, CUtlBuffer& buf) = 0;
	virtual bool			UnzipFile(const char* pFileName, const char* pPath, const char* pDestination) = 0;
	*/

	virtual void sub_180018060() = 0;
	virtual void sub_18001CE80() = 0;
	virtual void sub_180015F20() = 0;
	virtual void sub_18000C540() = 0;
	virtual void qword_18001AD40_10h() = 0;
	virtual void sub_18001BFC0() = 0;
	virtual void sub_18001BD60() = 0;
	virtual void sub_18001BD20() = 0;
	virtual void sub_1800100F0() = 0;
	virtual void sub_180016850() = 0;
	virtual void sub_18000D850() = 0;
	virtual void sub_180014990() = 0;
	virtual void sub_18001B050() = 0;
	virtual void sub_180010560() = 0;
	virtual void sub_1800182C0() = 0;
	virtual void sub_18001CF20() = 0;
	virtual void sub_18001C9B0() = 0;
};

//-----------------------------------------------------------------------------
// Main file system interface
//-----------------------------------------------------------------------------

#define FILESYSTEM_INTERFACE_VERSION			"VFileSystem017"

abstract_class IFileSystem //: public IAppSystem, public IBaseFileSystem
{
public:
	virtual void sub_180009A50() = 0;
	virtual void sub_18000C7D0() = 0;
	virtual void sub_18000CBE0() = 0;
	virtual void CBaseFileSystem__QueryInterface() = 0;
	virtual void CBaseFileSystem__Init() = 0;
	virtual void CBaseFileSystem__Shutdown() = 0;
	virtual void sub_180010520() = 0;
	virtual void sub_180018D70() = 0;
	virtual void _purecall_0() = 0;
	virtual void _purecall_1() = 0;
	virtual void AddSearchPath(const char* pPath, const char* pathID, SearchPathAdd_t addType) = 0;
	virtual void sub_180019DB0() = 0;
	virtual void sub_180019AD0() = 0;
	virtual void sub_18001A000() = 0;
	virtual void sub_1800158A0() = 0;
	virtual void sub_180018DE0() = 0;
	virtual void sub_180010FC0() = 0;
	virtual void sub_18000A690() = 0;
	virtual void sub_180019C20() = 0;
	virtual void CBaseFileSystem__ParsePathID() = 0;
	virtual void sub_18000C990() = 0;
	virtual void sub_180014200() = 0;
	virtual void sub_18000D980() = 0;
	virtual void sub_18001AF10() = 0;
	virtual void sub_180014D40() = 0;
	virtual void sub_18000D060() = 0;
	virtual void sub_180018910() = 0;
	virtual void sub_18000D3F0() = 0;
	virtual void CBaseFileSystem__LoadModule() = 0;
	virtual void CBaseFileSystem__UnloadModule() = 0;
	virtual void sub_18000F0D0() = 0;
	virtual void sub_18000F910() = 0;
	virtual void sub_18000F8F0() = 0;
	virtual void sub_18000DEF0() = 0;
	virtual void sub_18000F0E0() = 0;
	virtual void sub_18000E330() = 0;
	virtual void sub_180010910() = 0;
	virtual void sub_1800101D0() = 0;

	// Gets the current working directory
	virtual bool GetCurrentDirectory(char* pDirectory, int maxlen) = 0;

	virtual void sub_18000FCA0() = 0;
	virtual void qword_18001BED0_20h() = 0;
	virtual void sub_18001E9F0() = 0;
	virtual void sub_18000C1D0() = 0;
	virtual void sub_18001E610() = 0;
	virtual void sub_18001E8D0() = 0;
	virtual void sub_18001E920() = 0;
	virtual void sub_18001E980() = 0;
	virtual void sub_18001EC70() = 0;
	virtual void sub_18001EBE0() = 0;
	virtual void sub_18001E710() = 0;
	virtual void sub_18001E870() = 0;
	virtual void sub_18001E890() = 0;
	virtual void sub_18001E9A0() = 0;
	virtual void sub_18001E5D0() = 0;
	virtual void sub_18001EC60() = 0;
	virtual void sub_18001EC00() = 0;
	virtual void sub_18001E5F0() = 0;
	virtual void sub_18001EBC0() = 0;
	virtual void _purecall_2() = 0;
	virtual void _purecall_3() = 0;
	virtual void _purecall_4() = 0;
	virtual void _purecall_5() = 0;
	virtual void _purecall_6() = 0;
	virtual void nullsub_16() = 0;
	virtual void sub_180016DB0() = 0;
	virtual void sub_180016DF0() = 0;
	virtual void sub_18001B5A0() = 0;
	virtual void sub_18001B5B0() = 0;
	virtual void sub_180009F00() = 0;
	virtual void sub_180019CF0() = 0;
	virtual void sub_180009EA0() = 0;
	virtual void sub_180019BB0() = 0;
	virtual void sub_18000D380() = 0;
	virtual void sub_180010840() = 0;
	virtual void sub_180015F50() = 0;
	virtual void sub_180018210() = 0;
	virtual void sub_1800183B0() = 0;
	virtual void sub_18000F0C0() = 0;
	virtual void sub_18001B5C0() = 0;
	virtual void sub_18000CAD0() = 0;
	virtual void sub_180015210() = 0;
	virtual void sub_180015180() = 0;
	virtual void sub_18001EC90() = 0;
	virtual void sub_18001EDB0() = 0;
	virtual void sub_18001EA20() = 0;
	virtual void sub_18001E750() = 0;
	virtual void CBaseFileSystem__GetFileTypeForFullPath() = 0;
	virtual void sub_180018AA0() = 0;
	virtual void sub_180010BA0() = 0;
	virtual void sub_18000C190() = 0;
	virtual void sub_180010190() = 0;
	virtual void sub_180014E80() = 0;
	virtual void sub_18001CD00() = 0;
	virtual void sub_18001A100() = 0;
	virtual void sub_180011760() = 0;
	virtual void sub_18000FE50() = 0;
	virtual void sub_18000FDF0() = 0;
	virtual void sub_18001CD60() = 0;
	virtual void sub_18001CD70() = 0;
	virtual void sub_180014E70() = 0;
	virtual void qword_18001BED0_10h() = 0;
	virtual void sub_1800166C0() = 0;
	virtual void sub_180009DB0() = 0;
	virtual void sub_18001B4D0() = 0;
	virtual void sub_18001B590() = 0;
	virtual void sub_1800166B0() = 0;
	virtual void sub_180014E90() = 0;
	virtual void sub_180011850() = 0;
	virtual void sub_180010C40() = 0;
	virtual void sub_180011780() = 0;
	virtual void sub_180010AB0() = 0;
	virtual void sub_18000BEA0() = 0;
	virtual void sub_18001A120() = 0;
	virtual void sub_18000C290() = 0;
	virtual void sub_18000CF60() = 0;
	virtual void sub_18001CD20() = 0;
	virtual void sub_18001CD80() = 0;
	virtual void sub_18001CD90() = 0;
	virtual void sub_18000CC40() = 0;
	virtual void sub_1800108F0() = 0;
	virtual void sub_1800101F0() = 0;
	virtual void sub_180010DD0() = 0;
	virtual void sub_180010E60() = 0;
	virtual void sub_180011290() = 0;
	virtual void sub_180019A40() = 0;
	virtual void sub_180011650() = 0;
	virtual void sub_18001B250() = 0;
	virtual void sub_1800108C0() = 0;
	virtual void _purecall_7() = 0;
	virtual void _purecall_8() = 0;
	virtual void _purecall_9() = 0;
	virtual void _purecall_10() = 0;
	virtual void _purecall_11() = 0;
	virtual void _purecall_12() = 0;
	virtual void _purecall_13() = 0;
	virtual void _purecall_14() = 0;
	virtual void sub_18000D4F0() = 0;
	virtual void _purecall_15() = 0;
	virtual void _purecall_16() = 0;
	virtual void _purecall_17() = 0;
	virtual void _purecall_18() = 0;
	virtual void _purecall_19() = 0;
	virtual void _purecall_20() = 0;
	virtual void _purecall_21() = 0;
	virtual void _purecall_22() = 0;
	virtual void _purecall_23() = 0;
	virtual void sub_18000D4C0() = 0;
};

extern IFileSystem* g_pFullFileSystem;