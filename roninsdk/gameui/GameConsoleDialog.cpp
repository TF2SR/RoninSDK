#include "GameConsoleDialog.h"
#include "GameConsole.h"
#include "core/logdef.h"

void CGameConsoleDialog__OnCommandSubmitted(void* self, const char* pCommand)
{
	v_CGameConsoleDialog__OnCommandSubmitted(self, pCommand);
	DevMsg(eDLL_T::NONE, "] %s\n", pCommand);
}

void VConsoleDialog::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CGameConsoleDialog__OnCommandSubmitted, &CGameConsoleDialog__OnCommandSubmitted);
}

void VConsoleDialog::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CGameConsoleDialog__OnCommandSubmitted, &CGameConsoleDialog__OnCommandSubmitted);
}