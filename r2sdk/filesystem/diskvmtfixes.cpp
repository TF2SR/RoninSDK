#include "diskvmtfixes.h"

void VDiskVMTFixes::Attach(void) const
{
	// in retail VMTs will never load if cache read is invalid due to a special case for them in KeyValues::LoadFromFile
	// this effectively makes it impossible to load them from mods because we invalidate cache for doing this
	// so uhh, stop that from happening

	// tbh idk why they even changed any of this what's the point it looks like it works fine who cares my god

	// matsystem KeyValues::LoadFromFile: patch special case on cache read failure for vmts
	g_pMatSys_DX11Dll->Offset(0x1281B9).Patch({ 0xEB });

	// CMaterialSystem::FindMaterial: don't call function that crashes if previous patch is applied
	g_pMatSys_DX11Dll->Offset(0x5F55A).SetNOP(5);
}

void VDiskVMTFixes::Detach(void) const
{

}