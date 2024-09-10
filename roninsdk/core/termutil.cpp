#include "core/stdafx.h"
#include "core/termutil.h"

string g_svGreyF = "";
string g_svRedF = "";
string g_svGreenF = "";
string g_svBlueF = "";
string g_svCyanF = "";
string g_svYellowF = "";

string g_svGreyB = "";
string g_svRedB = "";
string g_svGreenB = "";
string g_svBlueB = "";
string g_svYellowB = "";

string g_svReset = "";

string g_svCmdLine;

//-----------------------------------------------------------------------------
// Purpose: sets the global ansi escape sequences.
// If '-ansicolor' has not been passed to the sdk the char will be empty.
//-----------------------------------------------------------------------------
void AnsiColors_Init()
{
	g_svGreyF = "\033[38;2;204;204;204;48;2;000;000;000m";
	g_svRedF = "\033[38;2;255;000;000;48;2;000;000;000m";
	g_svGreenF = "\033[38;2;000;255;000;48;2;000;000;000m";
	g_svBlueF = "\033[38;2;000;000;255;48;2;000;000;000m";
	g_svCyanF = "\033[38;2;28;160;147;48;2;000;000;000m";
	g_svYellowF = "\033[38;2;255;255;000;48;2;000;000;000m";

	g_svGreyB = "\033[38;2;000;000;000;48;2;204;204;204m";
	g_svRedB = "\033[38;2;000;000;000;48;2;255;000;000m";
	g_svGreenB = "\033[38;2;000;000;000;48;2;000;255;000m";
	g_svBlueB = "\033[38;2;000;000;000;48;2;000;000;255m";
	g_svYellowB = "\033[38;2;000;000;000;48;2;255;255;000m";

	g_svReset = "\033[38;2;204;204;204;48;2;000;000;000m";
}