#pragma once
#include "squirrel/squirrelmanager.h"
#include "squirrel/sqfiles.h"

enum InputEventType_t
{
	IE_ButtonPressed = 0,	// m_nData contains a ButtonCode_t
	IE_ButtonReleased,		// m_nData contains a ButtonCode_t
	IE_ButtonDoubleClicked,	// m_nData contains a ButtonCode_t
	IE_AnalogValueChanged,	// m_nData contains an AnalogCode_t, m_nData2 contains the value

	IE_FirstSystemEvent = 100,
	IE_Quit = IE_FirstSystemEvent,
	IE_ControllerInserted,	// m_nData contains the controller ID
	IE_ControllerUnplugged,	// m_nData contains the controller ID

	IE_FirstVguiEvent = 1000,	// Assign ranges for other systems that post user events here
	IE_FirstAppEvent = 2000,
};

struct KeyInfo_t
{
	char			*m_pKeyBinding;
	unsigned char	m_nKeyUpTarget : 3;
	unsigned char	m_bKeyDown : 1;
};

inline CMemory p_KeyInfoArray;
inline auto v_KeyInfoArray = p_KeyInfoArray.RCast<KeyInfo_t*>();

inline CMemory p_CInputSystem__PostEvent;
inline auto v_CInputSystem__PostEvent = p_CInputSystem__PostEvent.RCast<void(*)(void* thisObject, InputEventType_t nType, int nTick, int nData, int nData2, int nData3)>();

inline CMemory p_EngineUpdate;
inline auto v_EngineUpdate = p_EngineUpdate.RCast<void(*)()>();

inline long long wallrunStartedTime = 0;
inline long long jumpHitTime = 0;
inline long long crouchHitTime = 0;
inline long long jumpSentTime = 0;

inline const int BUTTON_CODE_COUNT = 153;

struct InputHolder {
	void* thisObject;
	InputEventType_t nType;
	int nTick;
	int data1;
	int data2;
	int data3;

	bool waitingToSend;
	long long timestamp;

	void Hold(void* thisObject, InputEventType_t nType, int nTick, int data1, int data2, int data3)
	{
		this->thisObject = thisObject;
		this->nType = nType;
		this->nTick = nTick;
		this->data1 = data1;
		this->data2 = data2;
		this->data3 = data3;
		waitingToSend = true;
	}
	void Release()
	{
		v_CInputSystem__PostEvent(thisObject, nType, nTick, data1, data2, data3);
		waitingToSend = false;
	}
};

struct VInputSystemHooksCKF : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
		p_CInputSystem__PostEvent = g_pInputSystemDll->Offset(0x7EC0);
		v_CInputSystem__PostEvent = p_CInputSystem__PostEvent.RCast<void(*)(void* thisObject, InputEventType_t nType, int nTick, int nData, int nData2, int nData3)>();
		
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};

struct VEngineHooksCKF : public IDetour
{
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
		// this offset may seem fucked but it isnt, elad checked.
		// hes trust worthy. trust him. -elad
		p_KeyInfoArray = g_pEngineDll->Offset(0x1396C5C0);
		v_KeyInfoArray = p_KeyInfoArray.RCast<KeyInfo_t*>();

		p_EngineUpdate = g_pEngineDll->Offset(0x77f50);
		v_EngineUpdate = p_EngineUpdate.RCast<void(*)()>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const;
	virtual void Detach(void) const;
};

SQRESULT Script_Ronin_FindBindsCKF(HSquirrelVM* sqvm);

// ALL TIMES RELATIVE TO WALLRUN START.
// crouch hit, jump hit, jump/crouch send, frame jumped off, speed gained, frame rate

inline SQRESULT Script_Ronin_StartedWallrun(HSquirrelVM* sqvm)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	wallrunStartedTime = (ts.tv_nsec / 1000) + (ts.tv_sec * 1000000);
	DevMsg(eDLL_T::RONIN_CKF, "WALLRUN %i", wallrunStartedTime);
	return SQRESULT_NULL;
}

inline SQRESULT Script_Ronin_GetWallkickTiming(HSquirrelVM* sqvm)
{
	g_pSQManager<ScriptContext::CLIENT>->PushInteger(sqvm, jumpSentTime - wallrunStartedTime);
	return SQRESULT_NOTNULL;
}

inline SQRESULT Script_Ronin_AppendWallrun(HSquirrelVM* sqvm)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	long long real = (ts.tv_nsec / 1000) + (ts.tv_sec * 1000000);

	float speedGained = g_pSQManager<ScriptContext::CLIENT>->GetFloat(sqvm, 1);
	int frameJumpedOff = g_pSQManager<ScriptContext::CLIENT>->GetInteger(sqvm, 2);
	float frameRate = g_pSQManager<ScriptContext::CLIENT>->GetFloat(sqvm, 3); // idk how to measure this tbh

	char buffer[100];
	std::stringstream sstream;
	sstream << std::fixed;
	sstream << crouchHitTime - wallrunStartedTime << ",";
	sstream << jumpHitTime - wallrunStartedTime << ",";
	sstream << jumpSentTime - wallrunStartedTime << ",";
	sstream.precision(3);
	sstream << speedGained << ",";
	sstream << frameJumpedOff << ",";
	sstream.precision(3);
	sstream << frameRate;
	sstream << "\n";

	std::string data = sstream.str();

	fs::path path = SAVE_FILE_DIR;
	path.append("ckdata.csv");

	auto mutex = std::ref(g_pSaveFileManager->mutexMap[path]);
	std::thread writeThread([mutex, path, data]()
		{
			mutex.get().lock();

			fs::path dir = path.parent_path();
			fs::create_directories(dir);

			std::ofstream fileStr(path, std::ios::app);
			if (fileStr.fail())
			{
				mutex.get().unlock();
				return;
			}
			fileStr << data;
			fileStr.close();

			mutex.get().unlock();
		});
	writeThread.detach();

	return SQRESULT_NOTNULL;
}