#include "sqfiles.h"
#include "squirrelmanager.h"

// Saves a file asynchronously.
void SaveFileManager::SaveFileAsync(fs::path file, std::string contents)
{
	auto mutex = std::ref(mutexMap[file]);
	std::thread writeThread(
		[mutex, file, contents]()
		{
			try
			{
				mutex.get().lock();

				fs::path dir = file.parent_path();
				fs::create_directories(dir);

				std::ofstream fileStr(file);
				if (fileStr.fail())
				{
					mutex.get().unlock();
					return;
				}

				fileStr.write(contents.c_str(), contents.length());
				fileStr.close();

				mutex.get().unlock();
			}
			catch (std::exception ex)
			{
				DevMsg(eDLL_T::FS, "SAVE FAILED!");
				mutex.get().unlock();
				DevMsg(eDLL_T::FS, ex.what());
			}
		});

	writeThread.detach();
}

// Loads a file asynchronously.
void SaveFileManager::LoadFileAsync(fs::path file)
{
	FileResults* results = &resultsMap[file];
	auto mutex = std::ref(mutexMap[file]);
	std::thread readThread(
		[mutex, file, results]()
		{
			try
			{
				mutex.get().lock();

				std::ifstream fileStr(file);
				if (fileStr.fail())
				{
					spdlog::error("A file was supposed to be loaded but we can't access it?!");

					mutex.get().unlock();
					return;
				}

				std::stringstream stringStream;
				stringStream << fileStr.rdbuf();

				results->success = true;
				results->readResult = stringStream.str();
				fileStr.close();
				mutex.get().unlock();
				// side-note: this causes a leak?
				// when a file is added to the map, it's never removed.
				// no idea how to fix this - because we have no way to check if there are other threads waiting to use this file(?)
				// tried to use m.try_lock(), but it's unreliable, it seems.
			}
			catch (std::exception ex)
			{
				spdlog::error("LOAD FAILED!");
				mutex.get().unlock();
				spdlog::error(ex.what());
			}
		});

	readThread.detach();
}

// Deletes a file asynchronously.
void SaveFileManager::DeleteFileAsync(fs::path file)
{
	// P.S. I don't like how we have to async delete calls but we do.
	auto m = std::ref(mutexMap[file]);
	std::thread deleteThread(
		[m, file]()
		{
			try
			{
				m.get().lock();

				fs::remove(file);

				m.get().unlock();
				// side-note: this causes a leak?
				// when a file is added to the map, it's never removed.
				// no idea how to fix this - because we have no way to check if there are other threads waiting to use this file(?)
				// tried to use m.try_lock(), but it's unreliable, it seems.
			}
			catch (std::exception ex)
			{
				spdlog::error("DELETE FAILED!");
				m.get().unlock();
				spdlog::error(ex.what());
			}
		});

	deleteThread.detach();
}

SQRESULT Script_SaveFile(HSquirrelVM* sqvm)
{
	fs::path path = SAVE_FILE_DIR;
	path.append(g_pSQManager<ScriptContext::UI>->GetString(sqvm, 1));

	std::string contents = g_pSQManager<ScriptContext::UI>->GetString(sqvm, 2);

	g_pSaveFileManager->SaveFileAsync(path, contents);

	return SQRESULT_NULL;
}

// loads a file asynchronously
SQRESULT Script_LoadFile(HSquirrelVM* sqvm)
{
	fs::path path = SAVE_FILE_DIR;
	path.append(g_pSQManager<ScriptContext::UI>->GetString(sqvm, 1));

	g_pSaveFileManager->LoadFileAsync(path);

	return SQRESULT_NULL;
}

// returns all files in a directory
SQRESULT Script_GetFilesInDir(HSquirrelVM* sqvm)
{
	fs::path path = SAVE_FILE_DIR;
	path.append(g_pSQManager<ScriptContext::UI>->GetString(sqvm, 1));

	g_pSQManager<ScriptContext::UI>->NewArray(sqvm, 0);
	if (!fs::exists(path))
		return SQRESULT_NOTNULL;
	for (const auto& entry : fs::directory_iterator(path))
	{
		g_pSQManager<ScriptContext::UI>->PushString(sqvm, entry.path().filename().string().c_str(), -1);
		g_pSQManager<ScriptContext::UI>->ArrayAppend(sqvm, -2);
	}
	return SQRESULT_NOTNULL;
}

SQRESULT Script_FileExists(HSquirrelVM* sqvm)
{
	fs::path path = SAVE_FILE_DIR;
	path.append(g_pSQManager<ScriptContext::UI>->GetString(sqvm, 1));

	g_pSQManager<ScriptContext::UI>->PushBool(sqvm, fs::exists(path));
	return SQRESULT_NOTNULL;
}

SQRESULT Script_DeleteFile(HSquirrelVM* sqvm)
{
	fs::path path = "./ronin/data";
	path.append(g_pSQManager<ScriptContext::UI>->GetString(sqvm, 1));
	
	g_pSaveFileManager->DeleteFileAsync(path);

	return SQRESULT_NULL;
}

// returns if we have finished reading a file's contents
SQRESULT Script_IsFileReady(HSquirrelVM* sqvm)
{
	fs::path path = "./ronin/data";
	path.append(g_pSQManager<ScriptContext::UI>->GetString(sqvm, 1));

	if (g_pSaveFileManager->resultsMap.find(path) == g_pSaveFileManager->resultsMap.end())
	{
		g_pSQManager<ScriptContext::UI>->RaiseError(sqvm, "There was no LoadFile call for this file!");
		return SQRESULT_ERROR;
	}

	bool result = g_pSaveFileManager->mutexMap[path].try_lock();
	g_pSaveFileManager->mutexMap[path].unlock();
	g_pSQManager<ScriptContext::UI>->PushBool(sqvm, result);
	return SQRESULT_NOTNULL;
}

// this will block the thread until the file is ready
// to be read!
SQRESULT Script_GetFileResults(HSquirrelVM* sqvm)
{
	fs::path path = "./ronin/data";
	path.append(g_pSQManager<ScriptContext::UI>->GetString(sqvm, 1));

	if (g_pSaveFileManager->resultsMap.find(path) == g_pSaveFileManager->resultsMap.end())
	{
		g_pSQManager<ScriptContext::UI>->RaiseError(sqvm, "There was no LoadFile call for this file!");
		return SQRESULT_ERROR;
	}

	auto m = std::ref(g_pSaveFileManager->mutexMap.at(path));
	m.get().lock();

	std::string results = g_pSaveFileManager->resultsMap[path].readResult;
	g_pSQManager<ScriptContext::UI>->PushString(sqvm, results.c_str(), results.length());

	m.get().unlock();
	g_pSaveFileManager->resultsMap.erase(path);
	return SQRESULT_NOTNULL;
}