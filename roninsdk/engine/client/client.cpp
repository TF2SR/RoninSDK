#include "client.h"

bool CClient__Connect(void* self, const char* szName, void* pNetChannel, bool bFakePlayer, void* a5, char* szMessage, void* a7)
{
	DevMsg(eDLL_T::NONE, "CClient__Connect\n");
	bool bRet = v_CClient__Connect(self, szName, pNetChannel, bFakePlayer, a5, szMessage, a7);

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
void VClient::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CClient__Connect, &CClient__Connect);
}

void VClient::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CClient__Connect, &CClient__Connect);
}