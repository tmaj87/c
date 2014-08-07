#include "header.h"

tPlat_FloatTime Plat_FloatTime;

base::base()
{
	debug = new dbg();
	debug->cleanFile();
	initFaces();
}

void base::initFaces()
{
	// wait till modules load
	while (hEngine == NULL)
	{
		hEngine = GetModuleHandle("engine.dll");
		Sleep(100);
	}
	while (hClient == NULL)
	{
		hClient = GetModuleHandle("client.dll");
		Sleep(100);
	}
	while (hVGui == NULL)
	{
		hVGui = GetModuleHandle("vguimatsurface.dll");
		Sleep(100);
	}
	while (hVGui2 == NULL)
	{
		hVGui2 = GetModuleHandle("vgui2.dll");
		Sleep(100);
	}
	while (hTier0 == NULL)
	{
		hTier0 = GetModuleHandle("tier0.dll");
		Sleep(100);
	}

	// funny way of doing this
	g_pEngineFactory = (tCreateInterface)GetProcAddress(hEngine, "CreateInterface");
	g_ClientFactory = (tCreateInterface)GetProcAddress(hClient, "CreateInterface");
	g_VGUIFactory = (tCreateInterface)GetProcAddress(hVGui, "CreateInterface");
	g_VGUI2Factory = (tCreateInterface)GetProcAddress(hVGui2, "CreateInterface");

	// ...
	g_pEngine = (EngineClient*)g_pEngineFactory("VEngineClient013", NULL);
	g_pEntList = (CEntList*)g_ClientFactory("VClientEntityList003", NULL);
	g_pSurface = (ISurface*)g_VGUIFactory("VGUI_Surface031", NULL);
	g_pIPanel = (IPanel*)g_VGUI2Factory("VGUI_Panel009", NULL);
	//g_pDebug = (IVDebugOverlay*)g_pEngineFactory("VDebugOverlay004", NULL);
	g_pClient = (IBaseClientDLL*)g_ClientFactory("VClient018", NULL);

	Plat_FloatTime = (tPlat_FloatTime)GetProcAddress(hTier0, "Plat_FloatTime");

	engineTrace = (EngineTraceClient004*)g_pEngineFactory("EngineTraceClient004", NULL);

	if (SHOW_DEBUG)
	{
		char buff[64] = { 0 };
		sprintf_s(buff, "engineTrace: %p\n", engineTrace);
		debug->toFile(buff);
	}
}


float hack::getDist(Vector& myCoords, Vector& enemyCoords)
{
	return (float)sqrt(
		pow(enemyCoords[0] - myCoords[0], 2.0) +
		pow(enemyCoords[1] - myCoords[1], 2.0) +
		pow(enemyCoords[2] - myCoords[2], 2.0));
}

bool hack::w2s(Vector &vOrigin, Vector &vScreen) {
	const matrix3x4& worldToScreen = *m_vMatrix;

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	vScreen.z = 0;

	if (w > .001)
	{
		int wScreen, hScreen;
		core->g_pEngine->GetScreenSize(wScreen, hScreen);

		float fl1DBw = 1 / w;

		vScreen.x = int((wScreen / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * wScreen + 0.5));
		vScreen.y = int((hScreen / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * hScreen + 0.5));
		return 1;
	}

	return 0;
}

void hack::inTheMiddle(VPANEL vguiPanel)
{
	static int w, h;
	core->g_pIPanel->GetSize(vguiPanel, w, h);
	core->g_pSurface->DrawSetColor(255, 20, 147, 160);
	core->g_pSurface->DrawLine(w / 2 - 5, h / 2, w / 2 + 5, h / 2);
	core->g_pSurface->DrawLine(w / 2, h / 2 - 5, w / 2, h / 2 + 5);
}

void hack::drawOff()
{
	const wchar_t offStr[] = L"off";
	core->g_pSurface->DrawSetTextFont(0);
	core->g_pSurface->DrawSetTextColor(255, 0, 0, 200);
	core->g_pSurface->DrawSetTextPos(10, 10);
	core->g_pSurface->DrawPrintText(offStr, wcslen(offStr));
}

void hack::getMatrix()
{
	cvmth64* clientHook = new cvmth64;

	if (!clientHook->bInitialize((PDWORD64*)core->g_pClient))
	{
		//
	}

	DWORD_PTR dwFunc1 = (DWORD_PTR)clientHook->dwGetMethodAddress(74) + 0x6;
	DWORD_PTR dwRenderHolder = (DWORD_PTR)((*(DWORD*)(dwFunc1 + 0x3)) + (dwFunc1 + 0x7)); // cut 4 bytes

	CViewRender* pRender;
	do {
		Sleep(50);
		pRender = *(CViewRender**)dwRenderHolder;
	} while (!pRender);

	m_vMatrix = pRender->GetWorldToScreenMatrix();
}

void hack::drawPlayer(CBaseEntity* player)
{
	static Vector headBone, screenPos;
	static Vector screenBottom, boneBottom;
	static Vector boneTop, screenTop;
	static int iSize;
	static int iWidth, iHeight;
	static matrix3x4 boneList[128];

	if (player->SetupBones(boneList, 128, 256, Plat_FloatTime()))
	{
		if (boneList[11][2][3] > boneList[12][2][3]) // head bones
		{
			headBone = Vector(boneList[11][0][3], boneList[11][1][3], boneList[11][2][3]);
		}
		else
		{
			headBone = Vector(boneList[12][0][3], boneList[12][1][3], boneList[12][2][3]);
		}
		boneTop = headBone + Vector(0, 0, 8);
		boneBottom = headBone - Vector(0, 0, 8);

		if (
			w2s(boneTop, screenTop)
			&& w2s(boneBottom, screenBottom)
			&& w2s(headBone, screenPos)
			)
		{
			iSize = (screenBottom.y - screenTop.y) / 2;
			// sign
			core->g_pSurface->DrawLine(screenPos.x - iSize/4, screenPos.y, screenPos.x + iSize/4, screenPos.y);
			core->g_pSurface->DrawLine(screenPos.x, screenPos.y - iSize/4, screenPos.x, screenPos.y + iSize/4);
			// left head bracket
			core->g_pSurface->DrawLine(screenPos.x - iSize, screenPos.y - iSize, screenPos.x - iSize, screenPos.y + iSize);
			core->g_pSurface->DrawLine(screenPos.x - iSize, screenPos.y - iSize, screenPos.x - iSize + iSize / 3, screenPos.y - iSize);
			core->g_pSurface->DrawLine(screenPos.x - iSize, screenPos.y + iSize, screenPos.x - iSize + iSize / 3, screenPos.y + iSize);
			// right head bracket
			core->g_pSurface->DrawLine(screenPos.x + iSize, screenPos.y - iSize, screenPos.x + iSize, screenPos.y + iSize);
			core->g_pSurface->DrawLine(screenPos.x + iSize - iSize / 3, screenPos.y - iSize, screenPos.x + iSize, screenPos.y - iSize);
			core->g_pSurface->DrawLine(screenPos.x + iSize - iSize / 3, screenPos.y + iSize, screenPos.x + iSize, screenPos.y + iSize);
			
			if (
				getDist(myPlayer->GetAbsOrigin(), headBone) < 1000
				&& *(int*)(DWORD64(myPlayer) + m_iTeamNum) != *(int*)(DWORD64(player) + m_iTeamNum)
				)
			{
				core->g_pSurface->DrawSetColor(255, 0, 0, 80);
				core->g_pEngine->GetScreenSize(iWidth, iHeight);
				core->g_pSurface->DrawLine(screenPos.x, screenPos.y, iWidth / 2, iHeight / 2);
			}
		}
	}
}

void hack::drawTitan(CBaseEntity* player)
{
	static Vector playerPos, screenPos;
	static Vector boneTop, boneBottom;
	static Vector screenTop, screenBottom;
	static int iSize;

	playerPos = player->GetAbsOrigin();
	boneTop = playerPos + Vector(0, 0, 100);
	boneBottom = playerPos - Vector(0, 0, 100);
	if (
		w2s(boneTop, screenTop)
		&& w2s(boneBottom, screenBottom)
		&& w2s(playerPos, screenPos)
		)
	{
		iSize = (screenBottom.y - screenTop.y) / 2;
		core->g_pSurface->DrawLine(screenPos.x - iSize, screenPos.y, screenPos.x + iSize, screenPos.y);
		core->g_pSurface->DrawLine(screenPos.x - iSize / 2, screenPos.y - iSize * 2, screenPos.x + iSize / 2, screenPos.y - iSize * 2);
	}
}

void hack::drawMinion(CBaseEntity* player)
{
	Vector headBone, screenPos;
	static Vector screenBottom, boneBottom;
	static Vector boneTop, screenTop;
	static int iSize;
	static int iWidth, iHeight;
	static matrix3x4 boneList[128];

	if (player->SetupBones(boneList, 128, 256, Plat_FloatTime()))
	{
		headBone = Vector(boneList[12][0][3], boneList[12][1][3], boneList[12][2][3]);

		boneTop = headBone + Vector(0, 0, 4);
		boneBottom = headBone - Vector(0, 0, 4);

		if (
			w2s(boneTop, screenTop)
			&& w2s(boneBottom, screenBottom)
			&& w2s(headBone, screenPos)
			)
		{
			iSize = (screenBottom.y - screenTop.y) / 2;
			core->g_pSurface->DrawLine(screenPos.x - iSize, screenPos.y, screenPos.x + iSize, screenPos.y);
			core->g_pSurface->DrawLine(screenPos.x, screenPos.y - iSize, screenPos.x, screenPos.y + iSize);
		}
		if (
			getDist(myPlayer->GetAbsOrigin(), headBone) < 1000
			&& *(int*)(DWORD64(myPlayer) + m_iTeamNum) != *(int*)(DWORD64(player) + m_iTeamNum)
			)
		{
			core->g_pSurface->DrawSetColor(255, 255, 0, 40);
			core->g_pEngine->GetScreenSize(iWidth, iHeight);
			core->g_pSurface->DrawLine(screenPos.x, screenPos.y, iWidth / 2, iHeight / 2);
		}
	}
}

void hack::drawOnRadar(Vector& screenPos)
{
	static int w, h, x2, y2;
	core->g_pEngine->GetScreenSize(w, h);
	if (screenPos.x < w / 2)
	{
		x2 = w / 2 - (w / 2 - screenPos.x) / 8;
	}
	else
	{
		x2 = w / 2 + (screenPos.x - w / 2) / 8;
	}
	y2 = h - (h - screenPos.y) / 8;
	core->g_pSurface->DrawLine(w / 2, h - 50, x2, y2 - 50);
}

bool hack::traceray(CBaseEntity* me, CBaseEntity* you)
{
	Ray_t ray;
	trace_t tr;
	
	ray.Init(me->GetAbsOrigin(), you->GetAbsOrigin());

	core->engineTrace->TraceRay(ray, 0x4600400B, NULL, &tr);

	if (tr.m_pEnt == you && tr.fractionleftsolid == 1.0f)
	{
		return 1;
	}
	return 0;
}