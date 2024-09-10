
#include "vengineserver_impl.h"

void CVEngineServer__SpewOutputFunc(void* pEngineServer, SpewType_t type, const char* fmt, va_list args)
{
	bool bShouldFormat = true;

	// because titanfall 2 is quite possibly the worst thing to yet exist, it sometimes gives invalid specifiers which will crash
	// ttf2sdk had a way to prevent them from crashing but it doesnt work in debug builds
	// so we use this instead
	for (int i = 0; fmt[i]; i++)
	{
		if (fmt[i] == '%')
		{
			switch (fmt[i + 1])
			{
				// this is fucking awful lol
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'f':
			case 'F':
			case 'g':
			case 'G':
			case 'a':
			case 'A':
			case 'c':
			case 's':
			case 'p':
			case 'n':
			case '%':
			case '-':
			case '+':
			case ' ':
			case '#':
			case '*':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				break;

			default:
			{
				bShouldFormat = false;
				break;
			}
			}
		}
	}

	// TODO [Fifty]: Let user choose log level as to not spam the console too much

	if (bShouldFormat)
		CoreMsgV(LogType_t::LOG_INFO, LogLevel_t::LEVEL_CONSOLE, eDLL_T::ENGINE, "sdk", fmt, args);
	else
		Warning(eDLL_T::ENGINE, "Failed to format string: '%s'\n", fmt);
}

void VEngineServer::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CVEngineServer__SpewOutputFunc, &CVEngineServer__SpewOutputFunc);
}

void VEngineServer::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CVEngineServer__SpewOutputFunc, &CVEngineServer__SpewOutputFunc);
}