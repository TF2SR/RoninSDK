#include "squirrel/sqclasstypes.h"
#include "squirrel/squirrelmanager.h"
#pragma once

SQRESULT Script_Ronin_GetPlayerPlatformVelocity(HSquirrelVM* sqvm);
SQRESULT Script_Ronin_SetServerPlayer(HSquirrelVM* sqvm);
SQRESULT Script_Ronin_AppendServerSquirrelBuffer(HSquirrelVM* sqvm);

inline CMemory svPlayer;