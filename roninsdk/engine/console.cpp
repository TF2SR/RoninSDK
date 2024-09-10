#include "console.h"

#include "gameui/GameConsole.h"

//-----------------------------------------------------------------------------
// Purpose: toggles the console
//-----------------------------------------------------------------------------
void Con_ToggleConsole_f(const CCommand& arg)
{
	if (g_pGameConsole->IsConsoleVisible())
	{
		g_pGameConsole->Hide();
	}
	else
	{
		g_pGameConsole->Activate();
	}
}

//-----------------------------------------------------------------------------
// Purpose: hides the console
//-----------------------------------------------------------------------------
void Con_HideConsole_f(const CCommand& arg)
{
	g_pGameConsole->Hide();
}

//-----------------------------------------------------------------------------
// Purpose: shows the console
//-----------------------------------------------------------------------------
void Con_ShowConsole_f(const CCommand& arg)
{
	g_pGameConsole->Activate();
}