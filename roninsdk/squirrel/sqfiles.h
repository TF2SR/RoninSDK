#pragma once
#include "squirrel/sqclasstypes.h"

inline const char* SAVE_FILE_DIR = "./ronin/data";

struct FileResults
{
	bool success = false;
	std::string readResult = "";
};

class SaveFileManager
{
public:
	void SaveFileAsync(fs::path file, std::string content);
	void LoadFileAsync(fs::path file);
	void DeleteFileAsync(fs::path file);
	std::map<fs::path, FileResults> resultsMap;
	std::map<fs::path, std::mutex> mutexMap;
};

inline SaveFileManager* g_pSaveFileManager;

SQRESULT Script_DeleteFile(HSquirrelVM* sqvm);
SQRESULT Script_SaveFile(HSquirrelVM* sqvm);
SQRESULT Script_LoadFile(HSquirrelVM* sqvm);
SQRESULT Script_IsFileReady(HSquirrelVM* sqvm);
SQRESULT Script_GetFileResults(HSquirrelVM* sqvm);
SQRESULT Script_GetFilesInDir(HSquirrelVM* sqvm);
