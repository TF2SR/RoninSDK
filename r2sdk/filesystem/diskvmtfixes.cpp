#include "diskvmtfixes.h"

void VDiskVMTFixes::Attach(void) const
{
	g_pMatSys_DX11Dll->Offset(0x1281B9).Patch({ 0xEB });
	g_pMatSys_DX11Dll->Offset(0x5F55A).SetNOP(5);
}

void VDiskVMTFixes::Detach(void) const
{

}