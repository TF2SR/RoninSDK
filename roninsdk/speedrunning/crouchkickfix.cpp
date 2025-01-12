#include "crouchkickfix.h"
#include "squirrel/sqclasstypes.h"
#include "squirrel/squirrelmanager.h"

std::vector<int> crouchCodes;
std::vector<int> jumpCodes;

InputHolder crouchHolder;
InputHolder jumpHolder;

void FindBinds()
{
	crouchCodes.clear();
	jumpCodes.clear();

	for (int i = 0; i < BUTTON_CODE_COUNT; i++)
	{
		KeyInfo_t keyInfo = v_KeyInfoArray[i];

		char* bind = keyInfo.m_pKeyBinding;

		if (IsBadReadPtrV2(bind))
			continue;

		DevMsg(eDLL_T::RONIN_CKF, "%i - %s %i %i", i, bind, strcmp(bind, "+ability 1"), strcmp(bind, "+duck"));
		if (strcmp(bind, "+ability 3") == 0) // jump bind
		{
			DevMsg(eDLL_T::RONIN_CKF, "pushing %i into jumpCodes", i);
			jumpCodes.push_back(i);
		}
		else if (strcmp(bind, "+duck") == 0)
		{
			DevMsg(eDLL_T::RONIN_CKF, "pushing %i into crouchCodes", i);
			crouchCodes.push_back(i);
		}
		else if (strcmp(bind, "+toggle_duck") == 0)
		{
			DevMsg(eDLL_T::RONIN_CKF, "pushing %i into crouchCodes", i);
			crouchCodes.push_back(i);
		}
	}
}

SQRESULT Script_Ronin_FindBindsCKF(HSquirrelVM* sqvm)
{
	FindBinds();
	return SQRESULT_NULL;
}

long long jumptime;
long long crouchtime;
void PostEventDetour(void* thisObject, InputEventType_t nType, int nTick, int data1, int data2, int data3)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	long long real = (ts.tv_nsec / 1000) + (ts.tv_sec * 1000000);
	// todo: when crouch/jump is press
	if (nType == IE_ButtonPressed)
	{
		if (std::find(jumpCodes.begin(), jumpCodes.end(), data1) != jumpCodes.end() && !jumpHolder.waitingToSend)
		{
			jumpHitTime = real;
			long sinceCrouch = real - crouchHolder.timestamp;
			DevMsg(eDLL_T::RONIN_CKF, "jump %i sinceCrouch %i", real, sinceCrouch);
			if (crouchHolder.waitingToSend && sinceCrouch <= CROUCHKICK_FIX_BUFFER_MICROSECONDS)
			{
				crouchHolder.Release();
				DevMsg(eDLL_T::RONIN_CKF, ("crouchkick: " + std::to_string(sinceCrouch / 1000.0f) + "ms CROUCH IS EARLY\n").c_str());
				jumpSentTime = real;
			}
			else
			{
				jumpHolder.Hold(thisObject, nType, nTick, data1, data2, data3);
				jumpHolder.timestamp = real;
				return;
			}
		}
		else if (std::find(crouchCodes.begin(), crouchCodes.end(), data1) != crouchCodes.end() && !crouchHolder.waitingToSend)
		{
			crouchHitTime = real;
			long sinceJump = real - jumpHolder.timestamp;
			DevMsg(eDLL_T::RONIN_CKF, "crouch %i sinceJump", real);
			if (jumpHolder.waitingToSend && sinceJump < CROUCHKICK_FIX_BUFFER_MICROSECONDS)
			{
				jumpHolder.Release();
				DevMsg(eDLL_T::RONIN_CKF, ("crouchkick: " + std::to_string(sinceJump / 1000.0f) + "ms JUMP IS EARLY\n").c_str());
				jumpSentTime = real;
			}
			else
			{
				crouchHolder.Hold(thisObject, nType, nTick, data1, data2, data3);
				crouchHolder.timestamp = real;
				return;
			}
		}
	}
	else if (nType == IE_ButtonReleased)
	{
		if (std::find(crouchCodes.begin(), crouchCodes.end(), data1) != crouchCodes.end())
		{
			if (crouchHolder.waitingToSend)
			{
				crouchHolder.Release();
			}
		}
		if (std::find(jumpCodes.begin(), jumpCodes.end(), data1) != jumpCodes.end())
		{
			if (jumpHolder.waitingToSend)
			{
				jumpHolder.Release();
			}
		}
	}
	v_CInputSystem__PostEvent(thisObject, nType, nTick, data1, data2, data3);
}

void UpdateDetour()
{
	v_EngineUpdate();

	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	long long real = (ts.tv_nsec / 1000) + (ts.tv_sec * 1000000);

	if (jumpHolder.waitingToSend) {
		long sinceJump = real - jumpHolder.timestamp;
		DevMsg(eDLL_T::RONIN_CKF, "%i", sinceJump);

		if (sinceJump > CROUCHKICK_FIX_BUFFER_MICROSECONDS) {
			jumpHolder.Release();
			jumpSentTime = real;

			long long e = jumpHolder.timestamp - crouchtime;

			DevMsg(eDLL_T::RONIN_CKF, ("jump released %i\n"), real);
			if (e < 100000) {
				DevMsg(eDLL_T::RONIN_CKF, ("not crouchkick: " + std::to_string(e / 1000.0f) + "ms CROUCH IS EARLY\n").c_str());
			}

			jumptime = jumpHolder.timestamp;
		}
	}

	if (crouchHolder.waitingToSend) {
		long sinceCrouch = real - crouchHolder.timestamp;
		DevMsg(eDLL_T::RONIN_CKF, "%i", sinceCrouch);

		if (sinceCrouch > CROUCHKICK_FIX_BUFFER_MICROSECONDS) {
			crouchHolder.Release();

			long long e = crouchHolder.timestamp - jumptime;

			DevMsg(eDLL_T::RONIN_CKF, ("crouch released\n"));
			if (e < 100000) {
				DevMsg(eDLL_T::RONIN_CKF, ("not crouchkick: " + std::to_string(e / 1000.0f) + "ms JUMP IS EARLY\n").c_str());
			}

			crouchtime = crouchHolder.timestamp;
		}
	}
}

void VInputSystemHooksCKF::Attach(void) const
{
	DetourAttach(&v_CInputSystem__PostEvent, &PostEventDetour);
}
void VInputSystemHooksCKF::Detach(void) const
{
	DetourDetach(&v_CInputSystem__PostEvent, &PostEventDetour);
}

void VEngineHooksCKF::Attach(void) const
{
	DetourAttach(&v_EngineUpdate, &UpdateDetour);
}
void VEngineHooksCKF::Detach(void) const
{
	DetourDetach(&v_EngineUpdate, &UpdateDetour);
}