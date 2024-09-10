#include "originauth.h"


char* Origin__Auth3PToken(void)
{
	//memset(g_psz3PToken, 0x0, 1024);
	//strcpy(g_psz3PToken, ORIGIN_3PTOKEN_REPLACEMENT);

	return v_Origin__Auth3PToken();
}

void Origin__AuthWithStryder(void* a1)
{
	//memset(g_psz3PToken, 0x0, 1024);
	//strcpy(g_psz3PToken, ORIGIN_3PTOKEN_REPLACEMENT);
	DevMsg(eDLL_T::NONE, "AuthWithStryder\n");
	v_Origin__AuthWithStryder(a1);
}


void VOrigin::Attach(void) const
{
	DetourAttach((LPVOID*)&v_Origin__Auth3PToken, &Origin__Auth3PToken);
	DetourAttach((LPVOID*)&v_Origin__AuthWithStryder, &Origin__AuthWithStryder);
}

void VOrigin::Detach(void) const
{
	DetourDetach((LPVOID*)&v_Origin__Auth3PToken, &Origin__Auth3PToken);
	DetourAttach((LPVOID*)&v_Origin__AuthWithStryder, &Origin__AuthWithStryder);
}