#pragma once
#include "mathlib/vector.h"
#include "mathlib/color.h"

enum OverlayType_t
{
	OVERLAY_BOX = 0,
	OVERLAY_SPHERE,
	OVERLAY_LINE,
	OVERLAY_SMARTAMMO,
	OVERLAY_TRIANGLE,
	OVERLAY_SWEPT_BOX,
	// [Elad]: thanks fifty :D
	// [Fifty]: the 2 bellow i did not confirm, rest are good
	OVERLAY_BOX2,
	OVERLAY_CAPSULE
};
struct OverlayBase_t
{
	OverlayBase_t()
	{
		m_Type = OVERLAY_BOX;
		m_nServerCount = -1;
		m_nCreationTick = -1;
		m_flEndTime = 0.0f;
		m_pNextOverlay = NULL;
	}

	OverlayType_t m_Type; // What type of overlay is it?
	int m_nCreationTick; // Duration -1 means go away after this frame #
	int m_nServerCount; // Latch server count, too
	float m_flEndTime; // When does this box go away
	OverlayBase_t* m_pNextOverlay;
	__int64 m_pUnk;
};

struct OverlayLine_t : public OverlayBase_t
{
	OverlayLine_t() { m_Type = OVERLAY_LINE; }

	Vector3D origin;
	Vector3D dest;
	int r;
	int g;
	int b;
	int a;
	bool noDepthTest;
};

struct OverlayBox_t : public OverlayBase_t
{
	OverlayBox_t() { m_Type = OVERLAY_BOX; }

	Vector3D origin;
	Vector3D mins;
	Vector3D maxs;
	QAngle angles;
	int r;
	int g;
	int b;
	int a;
};

struct OverlayTriangle_t : public OverlayBase_t
{
	OverlayTriangle_t() { m_Type = OVERLAY_TRIANGLE; }

	Vector3D p1;
	Vector3D p2;
	Vector3D p3;
	int r;
	int g;
	int b;
	int a;
	bool noDepthTest;
};

struct OverlaySweptBox_t : public OverlayBase_t
{
	OverlaySweptBox_t() { m_Type = OVERLAY_SWEPT_BOX; }

	Vector3D start;
	Vector3D end;
	Vector3D mins;
	Vector3D maxs;
	QAngle angles;
	int r;
	int g;
	int b;
	int a;
};

struct OverlaySphere_t : public OverlayBase_t
{
	OverlaySphere_t() { m_Type = OVERLAY_SPHERE; }

	Vector3D vOrigin;
	float flRadius;
	int nTheta;
	int nPhi;
	int r;
	int g;
	int b;
	int a;
	bool m_bWireframe;
};

inline bool (*OverlayBase_t__IsDead)(OverlayBase_t* a1);
inline void (*OverlayBase_t__DestroyOverlay)(OverlayBase_t* a1);

void __fastcall h_DrawAllOverlays(bool bRender); 
void __fastcall h_DrawOverlay(OverlayBase_t* pOverlay);

inline LPCRITICAL_SECTION s_OverlayMutex;

inline OverlayBase_t** s_pOverlays;

inline int* g_nRenderTickCount;
inline int* g_nOverlayTickCount;

inline void(__fastcall* o_pDrawOverlay)(OverlayBase_t* pOverlay) = nullptr;
inline void(__fastcall* o_pDrawAllOverlays)(bool bRender) = nullptr;

// Render Line
inline void (*RenderLine)(const Vector3D& v1, const Vector3D& v2, Color c, bool bZBuffer);

// Render box
inline void (*RenderBox)(
	const Vector3D& vOrigin, const QAngle& angles, const Vector3D& vMins, const Vector3D& vMaxs, Color c, bool bZBuffer, bool bInsideOut);

// Render wireframe box
inline void (*RenderWireframeBox)(
	const Vector3D& vOrigin, const QAngle& angles, const Vector3D& vMins, const Vector3D& vMaxs, Color c, bool bZBuffer, bool bInsideOut);

// Render swept box
inline void (*RenderWireframeSweptBox)(
	const Vector3D& vStart, const Vector3D& vEnd, const QAngle& angles, const Vector3D& vMins, const Vector3D& vMaxs, Color c, bool bZBuffer);

// Render Triangle
inline void (*RenderTriangle)(const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, Color c, bool bZBuffer);

// Render Axis
inline void (*RenderAxis)(const Vector3D& vOrigin, float flScale, bool bZBuffer);

// I dont know
inline void (*RenderUnknown)(const Vector3D& vUnk, float flUnk, bool bUnk);

// Render Sphere
inline void (*RenderSphere)(const Vector3D& vCenter, float flRadius, int nTheta, int nPhi, Color c, bool bZBuffer);

///////////////////////////////////////////////////////////////////////////////
class VDebugOverlays : public IDetour
{
	
	virtual void GetAdr(void) const
	{
	}
	virtual void GetFun(void) const
	{
		o_pDrawOverlay = g_pEngineDll->Offset(0xABCB0).RCast<decltype(o_pDrawOverlay)>();

		o_pDrawAllOverlays = g_pEngineDll->Offset(0xAB780).RCast<decltype(o_pDrawAllOverlays)>();

		OverlayBase_t__IsDead = g_pEngineDll->Offset(0xACAC0).RCast<decltype(OverlayBase_t__IsDead)>();
		OverlayBase_t__DestroyOverlay = g_pEngineDll->Offset(0xAB680).RCast<decltype(OverlayBase_t__DestroyOverlay)>();

		RenderLine = g_pEngineDll->Offset(0x192A70).RCast<decltype(RenderLine)>();
		RenderBox = g_pEngineDll->Offset(0x192520).RCast<decltype(RenderBox)>();
		RenderWireframeBox = g_pEngineDll->Offset(0x193DA0).RCast<decltype(RenderWireframeBox)>();
		RenderWireframeSweptBox = g_pEngineDll->Offset(0x1945A0).RCast<decltype(RenderWireframeSweptBox)>();
		RenderTriangle = g_pEngineDll->Offset(0x193940).RCast<decltype(RenderTriangle)>();
		RenderAxis = g_pEngineDll->Offset(0x1924D0).RCast<decltype(RenderAxis)>();
		RenderSphere = g_pEngineDll->Offset(0x194170).RCast<decltype(RenderSphere)>();
		RenderUnknown = g_pEngineDll->Offset(0x1924E0).RCast<decltype(RenderUnknown)>();

		s_OverlayMutex = g_pEngineDll->Offset(0x10DB0A38).RCast<LPCRITICAL_SECTION>();

		s_pOverlays = g_pEngineDll->Offset(0x10DB0968).RCast<OverlayBase_t**>();

		g_nRenderTickCount = g_pEngineDll->Offset(0x10DB0984).RCast<int*>();
		g_nOverlayTickCount = g_pEngineDll->Offset(0x10DB0980).RCast<int*>();

		// not in g_pCVar->FindVar by this point for whatever reason, so have to get from memory
	}
	virtual void GetVar(void) const {}
	virtual void GetCon(void) const {}
	virtual void Attach(void) const
	{
		DetourAttach(&(PVOID&)o_pDrawOverlay, (PVOID)h_DrawOverlay);
		DetourAttach(&(PVOID&)o_pDrawAllOverlays, (PVOID)h_DrawAllOverlays);
	};
	virtual void Detach(void) const {
		DetourDetach(&(PVOID&)o_pDrawOverlay, (PVOID)h_DrawOverlay);
		DetourDetach(&(PVOID&)o_pDrawAllOverlays, (PVOID)h_DrawAllOverlays);
	};
};
///////////////////////////////////////////////////////////////////////////////