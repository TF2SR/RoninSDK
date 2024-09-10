#include "vgui_baseui_interface.h"
#include "gameui/GameConsole.h"
#include "vgui_controls/Frame.h"
#include "vgui_controls/Label.h"
#include "vgui_controls/BitmapImagePanel.h"
#include "vgui_controls/ListPanel.h"
#include "core/logdef.h"
#include <tier0/memstd.h>
#include "filesystem.h"

char CEngineVGui__Init(void* self)
{
	char cResult = v_CEngineVGui__Init(self);
	DevMsg(eDLL_T::NONE, "CEngineVGui__Init: %i\n", cResult);
	g_pGameConsole->Initialize();

	//vgui::Frame* frame = MemAllocSingleton()->Alloc<vgui::Frame>(sizeof(vgui::Frame));
	//v_Frame__Frame(frame, NULL, "FrameTest", false, true);
	//frame->SetTitle("Test frame", true);
	//frame->SetVisible(true);

	//vgui::ListPanel* list = MemAllocSingleton()->Alloc<vgui::ListPanel>(sizeof(vgui::ListPanel));
	//v_ListPanel__ListPanel(list, frame, "ListPanelTest");
	//list->AddColumnHeader(0, "Please work", "what", 50, 50, 500);
	//list->AddActionSignalTarget(frame);

	//CBitmapImagePanel* image = MemAllocSingleton()->Alloc<CBitmapImagePanel>(sizeof(CBitmapImagePanel));
	//v_CBitmapImagePanel__CBitmapImagePanel(image, (vgui::Panel*)frame, "ImageTest", "vgui/spinner");

	//vgui::Label* label = MemAllocSingleton()->Alloc<vgui::Label>(sizeof(vgui::Label));
	//v_Label__Label(label, frame, "LabelTest", "Penis");
	//label->SetVisible(true);

	SpdLog_PostInit();
	return cResult;
}

void CEngineVGui__Shutdown(void* self)
{
	// This disables logging to GameConsole when shutting down
	// so that we dont try to log to it and AV
	g_bLogToGameConsole = false;
	v_CEngineVGui__Shutdown(self);
	DevMsg(eDLL_T::NONE, "CEngineVGui__Shutdown\n");
}

void VEngineVgui::Attach(void) const
{
	DetourAttach((LPVOID*)&v_CEngineVGui__Init, &CEngineVGui__Init);
	DetourAttach((LPVOID*)&v_CEngineVGui__Shutdown, &CEngineVGui__Shutdown);
}

void VEngineVgui::Detach(void) const
{
	DetourDetach((LPVOID*)&v_CEngineVGui__Init, &CEngineVGui__Init);
	DetourDetach((LPVOID*)&v_CEngineVGui__Shutdown, &CEngineVGui__Shutdown);
}