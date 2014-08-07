#pragma once
#include "sdk.h"
#include "debug.h"

#ifndef SHOW_DEBUG
	#define SHOW_DEBUG 1
#endif

class base
{
public:
	HINSTANCE hEngine;
	HINSTANCE hClient;
	HINSTANCE hVGui;
	HINSTANCE hVGui2;
	HINSTANCE hTier0;

	tCreateInterface g_pEngineFactory;
	tCreateInterface g_ClientFactory;
	tCreateInterface g_VGUIFactory;
	tCreateInterface g_VGUI2Factory;

	EngineClient* g_pEngine;
	CEntList* g_pEntList;
	ISurface* g_pSurface;
	IPanel* g_pIPanel;
	IBaseClientDLL* g_pClient;
	dbg* debug;
	EngineTraceClient004* engineTrace;

	base();
	void initFaces();
	void hook();
};

class hack
{
public:
	matrix3x4* m_vMatrix;

	float getDist(Vector& myCoords, Vector& enemyCoords);
	bool w2s(Vector &vOrigin, Vector &vScreen);
	void inTheMiddle(VPANEL vguiPanel);
	void drawOff();
	void getMatrix();
	void drawPlayer(CBaseEntity* model);
	void drawTitan(CBaseEntity* model);
	void drawMinion(CBaseEntity* model);
	void drawOnRadar(Vector& screenPos);
	bool traceray(CBaseEntity* me, CBaseEntity* you);
};

extern tPlat_FloatTime Plat_FloatTime;
extern base* core;
extern CBaseEntity* myPlayer;