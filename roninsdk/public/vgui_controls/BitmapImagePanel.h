//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef BITMAPIMAGEPANEL_H
#define BITMAPIMAGEPANEL_H

#include "Panel.h"

class CBitmapImagePanel : public vgui::Panel
{
public:
	//CBitmapImagePanel(vgui::Panel* parent, char const* panelName, char const* filename = NULL);

//	virtual void	PaintBackground();

	virtual void	setTexture(char const* filename);

	virtual void	forceReload(void);

private:
	bool			m_bUploaded;
	int				m_nTextureId;
	char			m_szTexture[128];
};

///////////////////////////////////////////////////////////////////////////////
inline CMemory p_CBitmapImagePanel__CBitmapImagePanel;
inline auto v_CBitmapImagePanel__CBitmapImagePanel = p_CBitmapImagePanel__CBitmapImagePanel.RCast<CBitmapImagePanel*(*)(CBitmapImagePanel* self, vgui::Panel* parent, char const* panelName, char const* filename)>();

///////////////////////////////////////////////////////////////////////////////
class VCBitmapImagePanel : public IDetour
{
	virtual void GetAdr(void) const
	{
		LogFunAdr("CBitmapImagePanel::CBitmapImagePanel", p_CBitmapImagePanel__CBitmapImagePanel.GetPtr());
	}
	virtual void GetFun(void) const
	{
		p_CBitmapImagePanel__CBitmapImagePanel = g_pClientDll->Offset(0x49F970);
		v_CBitmapImagePanel__CBitmapImagePanel = p_CBitmapImagePanel__CBitmapImagePanel.RCast<CBitmapImagePanel*(*)(CBitmapImagePanel*, vgui::Panel*, char const*, char const*)>();
	}
	virtual void GetVar(void) const { }
	virtual void GetCon(void) const { }
	virtual void Attach(void) const { }
	virtual void Detach(void) const { }
};
///////////////////////////////////////////////////////////////////////////////

#endif // BITMAPIMAGEPANEL_H