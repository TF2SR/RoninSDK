#include "debugoverlays.h"
#include "tier1/cvar.h"

void __fastcall h_DrawOverlay(OverlayBase_t* pOverlay)
{
	EnterCriticalSection(s_OverlayMutex);

	switch (pOverlay->m_Type)
	{
	case OVERLAY_SMARTAMMO:
	case OVERLAY_LINE:
	{
		OverlayLine_t* pLine = static_cast<OverlayLine_t*>(pOverlay);
		RenderLine(pLine->origin, pLine->dest, Color(pLine->r, pLine->g, pLine->b, pLine->a), pLine->noDepthTest);
	}
	break;
	case OVERLAY_BOX:
	{
		OverlayBox_t* pCurrBox = static_cast<OverlayBox_t*>(pOverlay);
		if (pCurrBox->a > 0)
		{
			RenderBox(
				pCurrBox->origin,
				pCurrBox->angles,
				pCurrBox->mins,
				pCurrBox->maxs,
				Color(pCurrBox->r, pCurrBox->g, pCurrBox->b, pCurrBox->a),
				false,
				false);
		}
		if (pCurrBox->a < 255)
		{
			RenderWireframeBox(
				pCurrBox->origin,
				pCurrBox->angles,
				pCurrBox->mins,
				pCurrBox->maxs,
				Color(pCurrBox->r, pCurrBox->g, pCurrBox->b, 255),
				false,
				false);
		}
	}
	break;
	case OVERLAY_TRIANGLE:
	{
		OverlayTriangle_t* pTriangle = static_cast<OverlayTriangle_t*>(pOverlay);
		RenderTriangle(
			pTriangle->p1,
			pTriangle->p2,
			pTriangle->p3,
			Color(pTriangle->r, pTriangle->g, pTriangle->b, pTriangle->a),
			pTriangle->noDepthTest);
	}
	break;
	case OVERLAY_SWEPT_BOX:
	{
		OverlaySweptBox_t* pBox = static_cast<OverlaySweptBox_t*>(pOverlay);
		RenderWireframeSweptBox(
			pBox->start, pBox->end, pBox->angles, pBox->mins, pBox->maxs, Color(pBox->r, pBox->g, pBox->b, pBox->a), false);
	}
	break;
	case OVERLAY_SPHERE:
	{
		OverlaySphere_t* pSphere = static_cast<OverlaySphere_t*>(pOverlay);
		RenderSphere(
			pSphere->vOrigin,
			pSphere->flRadius,
			pSphere->nTheta,
			pSphere->nPhi,
			Color(pSphere->r, pSphere->g, pSphere->b, pSphere->a),
			false);
	}
	break;
	default:
	{
		//spdlog::warn("Unimplemented overlay type {}", pOverlay->m_Type);
	}
	break;
	}

	LeaveCriticalSection(s_OverlayMutex);
}

void __fastcall h_DrawAllOverlays(bool bRender)
{
	EnterCriticalSection(s_OverlayMutex);

	OverlayBase_t* pCurrOverlay = *s_pOverlays; // rbx
	OverlayBase_t* pPrevOverlay = nullptr; // rsi
	OverlayBase_t* pNextOverlay = nullptr; // rdi

	int m_nCreationTick; // eax
	bool bShouldDraw; // zf
	int m_pUnk; // eax

	while (pCurrOverlay)
	{
		auto thing = OverlayBase_t__IsDead;

		if (thing(pCurrOverlay))
		{
			if (pPrevOverlay)
			{
				pPrevOverlay->m_pNextOverlay = pCurrOverlay->m_pNextOverlay;
			}
			else
			{
				*s_pOverlays = pCurrOverlay->m_pNextOverlay;
			}

			pNextOverlay = pCurrOverlay->m_pNextOverlay;
			OverlayBase_t__DestroyOverlay(pCurrOverlay);
			pCurrOverlay = pNextOverlay;
		}
		else
		{
			if (pCurrOverlay->m_nCreationTick == -1)
			{
				m_pUnk = pCurrOverlay->m_pUnk;

				if (m_pUnk == -1)
				{
					bShouldDraw = true;
				}
				else
				{
					bShouldDraw = m_pUnk == *g_nOverlayTickCount;
				}
			}
			else
			{
				bShouldDraw = pCurrOverlay->m_nCreationTick == *g_nRenderTickCount;
			}

			if (bShouldDraw && bRender && (Cvar_enable_debug_overlays->GetBool() || pCurrOverlay->m_Type == OVERLAY_SMARTAMMO))
			{
				h_DrawOverlay(pCurrOverlay);
			}

			pPrevOverlay = pCurrOverlay;
			pCurrOverlay = pCurrOverlay->m_pNextOverlay;
		}
	}

	LeaveCriticalSection(s_OverlayMutex);
}

