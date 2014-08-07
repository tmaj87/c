#include <Windows.h>
#include "VMT Hook.h"
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "sdk.h"

const DWORD m_iTeamNum = 0x98;
const DWORD m_iHealth = 0x90;
const DWORD m_lifeState = 0x8F;


inline float flGetDistance(Vector vOrigin, Vector vLocalOrigin) {
	Vector vDelta = vOrigin - vLocalOrigin;
	float m_fDistance = sqrt(vDelta.Length());
	if(m_fDistance < 1.0f) {
		return 1.0f;
	}
	return m_fDistance;
}

bool WorldToScreen(Vector &vOrigin, Vector &vScreen) {
	const matrix3x4& worldToScreen = g_pEngine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	vScreen.z = 0;

	if (w > .001) { //If the object is within view.
		int wScreen, hScreen;
		g_pEngine->GetScreenSize(wScreen, hScreen);

		float fl1DBw = 1 / w;

		vScreen.x = (wScreen / 2) + ( 0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * wScreen + 0.5); //Get the X dimension and push it in to the Vector.
		vScreen.y = (hScreen / 2) - ( 0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * hScreen + 0.5); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

bool ScreenTransform( const Vector &point, Vector &screen ) {
	float w;
	const matrix3x4 &worldToScreen = g_pEngine->WorldToScreenMatrix( );
	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w		 = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}
	return behind;
}

// -----------------------------------------------------------------------------

bool GetBonePosition(CBaseEntity* pPlayer, Vector& Hitbox, int Bone, int index = 3) {
	matrix3x4 MatrixArray[128];

	if(!pPlayer->SetupBones(MatrixArray, 128, 0x00000100, g_pEngine->Time())) {
		return false;
	}
	Hitbox = Vector(MatrixArray[Bone][0][index], MatrixArray[Bone][1][index], MatrixArray[Bone][2][index]);
	return true;
}

void DrawLine(int x0, int y0, int x1, int y1) {
	g_pSurface->DrawSetTextColor(255, 0, 0, 250);
	g_pSurface->DrawLine(x0, y0, x1, y1);
}

// ---------------------------------------------------------------------

void DrawString(int x, int y, int alpha, const char *pszText, ... ) {
	if(pszText == NULL) {
		return;
	}

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf_s( szBuffer, pszText, va_alist );
	va_end( va_alist );

	wsprintfW( szString, L"%S", szBuffer );

	g_pSurface->DrawSetTextPos(x, y);
	g_pSurface->DrawSetTextFont(drawFont);
	g_pSurface->DrawSetTextColor(0, 0, 255, alpha);
	g_pSurface->DrawPrintText(szString, wcslen(szString));
}

void GetBonesDebug(CBaseEntity* model, int bones[][2]) {
	matrix3x4 MatrixArray[128];
	if(!model->SetupBones(MatrixArray, 128, 0x00000100, g_pEngine->Time())) {
		return;
	}

	Vector vTmp1, vTmp2;
	int usedBones[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,28,29,30,31};
	for (int i = 0; i < sizeof(usedBones)/sizeof(*usedBones); i++) {
		vTmp1 = Vector(MatrixArray[usedBones[i]][0][3], MatrixArray[usedBones[i]][1][3], MatrixArray[usedBones[i]][2][3]);
		if (WorldToScreen(vTmp1, vTmp2)) {
			bones[usedBones[i]][0] = vTmp2.x;
			bones[usedBones[i]][1] = vTmp2.y;
		}
	}
}

void DrawBoneDebug(CBaseEntity* target, int boneNum, bool enemy, int distance) {
	Vector bonePos, boneScreenPos;
	Vector modelPos = target->GetAbsOrigin();


	//for (int i = 0; i < 4; i++) {
		GetBonePosition(target, bonePos, boneNum); //, i);
		if(!WorldToScreen(bonePos, boneScreenPos)) {
			return;
			//continue;
		}
		//if (flGetDistance(bonePos, modelPos) > 10) {
			//return;
			//continue;
		//}
		int size = 13;
		if (distance > 2048) {
			distance = 2048;
		}
		if (distance > 24) {
			size = 1;
		} else {
			size -= distance/2;
		}
		int alpha = 60;
		if (distance > 50) {
			alpha -= 50;
		} else {
			alpha -= distance;
		}
		if (enemy) {
			g_pSurface->DrawSetColor(255, 0, 0, 255-alpha);
		} else {
			g_pSurface->DrawSetColor(0, 255, 0, alpha);
		}
		g_pSurface->DrawOutlinedRect(boneScreenPos.x-size, boneScreenPos.y-size, boneScreenPos.x+size, boneScreenPos.y+size);
		char buff[256] = {0};
		//sprintf_s(buff, "%d::%d", boneNum, i);
		sprintf_s(buff, "%d", boneNum);
		DrawString(boneScreenPos.x, boneScreenPos.y, 250-alpha, buff);
	//}
	
	//char buff[256] = {0};
	//sprintf_s(buff, "%d,  %d,  %d,  %d", boneNum, bonePos.x, bonePos.y, bonePos.z);
	//sprintf_s(buff, "%d", boneNum);
	//DrawString(boneScreenPos.x, boneScreenPos.y, 250-alpha, buff);
}

void DrawHead(CBaseEntity* model) {
	Vector vHead, vHeadTop, vScreen, vScreenTop;
	GetBonePosition(model, vHead, 14);
	vHeadTop = vHead + Vector(0, 0, 8);

	if (WorldToScreen(vHead, vScreen) && WorldToScreen(vHeadTop, vScreenTop)) {
		int	h = vScreenTop.y - vScreen.y;
		g_pSurface->DrawOutlinedRect(vScreenTop.x-h/2, vScreenTop.y+1, vScreen.x+h/2, vScreen.y+1);
		g_pSurface->DrawLine(vScreenTop.x-h/2, vScreenTop.y+1, vScreenTop.x+h/2, vScreenTop.y+1); // why..?
		g_pSurface->DrawLine(vScreenTop.x-h/2, vScreen.y-1, vScreenTop.x+h/2, vScreen.y-1); // why..?
	}
}

// ------------------------------------------------------------------------

void DrawEnemyESP(int index) {
	player_info_s pInfo;

	CBaseEntity* myPlayer = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
	if(index == myPlayer->GetIndex()) {
		return;
	}

	CBaseEntity* enemyPlayer = g_pEntList->GetClientEntity(index);
	if(enemyPlayer == NULL) {
		return;
	}

	int myTeam = *(int*)(DWORD(myPlayer)+m_iTeamNum);
	int enemyTeam = *(int*)(DWORD(enemyPlayer)+m_iTeamNum);
	bool enemy = true;
	if (myTeam == enemyTeam) {
		enemy = false;
		//return;
	}

	g_pEngine->GetPlayerInfo(index, &pInfo);
	if (!strlen(pInfo.name)) {
		return;
	}

	int enemyHealth = *(int*)(DWORD(enemyPlayer)+m_iHealth);
	if (enemyHealth < 2) {
		return;
	}

	if (enemyPlayer->IsDormant()) {
		return;
	}

	int enemylifeState = *(int*)(DWORD(enemyPlayer)+m_lifeState);
	if (!enemylifeState) {
		return;
	}

	// ka¿demu graczowi
	// losuje unikatowy
	// kolor;

	Vector myScreen;
	Vector enemyPos = enemyPlayer->GetAbsOrigin();
	Vector myPos = myPlayer->GetAbsOrigin();
	float dist = flGetDistance(myPos, enemyPos);
	if (dist > 150) {
		//return;
	}

	if (WorldToScreen(enemyPos, myScreen)) {
		// DRAW MODE 001:
		//g_pSurface->DrawSetColor(255, 0, 0, alpha);
		//g_pSurface->DrawOutlinedRect(myScreen.x-5, myScreen.y-5, myScreen.x+5, myScreen.y+5);
		
		// DRAW MODE 002:
		/*
		static BYTE bones[32] = {};
		for(int i = 0; i < 32; i++) {
			DrawBoneDebug(enemyPlayer, i, enemy, dist);
		}
		*/
		
		// DRAW MODE 003:
		static int bones[32][2] = {};
		GetBonesDebug(enemyPlayer, bones); // populate bones array

		int alpha = 255;
		if (enemy) {
			if (dist > 50) {
				alpha -= 200;
			} else {
				alpha -= dist*4;
			}
			g_pSurface->DrawSetColor(255, 0, 0, alpha);
		} else {
			if (dist > 30) {
				alpha = 30;
			} else {
				alpha = dist;
			}
			g_pSurface->DrawSetColor(0, 255, 0, alpha);
		}
		int legs[] = {8,7,6,5,0,1,2,3,4};
		for (int i = 0; i < 8; i++) {
			g_pSurface->DrawLine(bones[legs[i]][0], bones[legs[i]][1], bones[legs[i+1]][0], bones[legs[i+1]][1]);
		}
		int torso[] = {14,13,12,11,10,9,0};
		for (int i = 0; i < 6; i++) {
			g_pSurface->DrawLine(bones[torso[i]][0], bones[torso[i]][1], bones[torso[i+1]][0], bones[torso[i+1]][1]);
		}
		int hands[] = {31,30,29,28,12,15,16,17,18};
		for (int i = 0; i < 8; i++) {
			g_pSurface->DrawLine(bones[hands[i]][0], bones[hands[i]][1], bones[hands[i+1]][0], bones[hands[i+1]][1]);
		}
		DrawHead(enemyPlayer);
	}
	
	//char buff[128];
	//sprintf_s(buff, "%s :: %f %f %f", pInfo.name, enemyPos[0], enemyPos[1], enemyPos[2]);
	//MessageBoxA(NULL, buff, "", 0x00000000L);
}

// -------------------------------------------------------------------------------

void inTheMiddle() {
	int w,h;
	g_pEngine->GetScreenSize(w, h);
	g_pSurface->DrawSetColor(255, 20, 147, 255);
	g_pSurface->DrawOutlinedRect(w/2, h/2-5, w/2+1, h/2+5);
	g_pSurface->DrawOutlinedRect(w/2-5, h/2, w/2+5, h/2+1);
}

void __fastcall pt(void *thisptr, void *_EDX, unsigned int vguiPanel, bool forceRepaint, bool allowForce) {
	OriginalPaintTraverse(thisptr, vguiPanel, forceRepaint, allowForce);
	
	static unsigned int vguiMatSystemTopPanel;
	if (vguiMatSystemTopPanel == NULL) {
		const char* szName = g_pIPanel->GetName(vguiPanel);
		if(szName[0] == 'M' && szName[3] == 'S') { //Look for MatSystemTopPanel without using slow operations like strcmp or strstr.
			vguiMatSystemTopPanel = vguiPanel;
		}
	}
	
	if (vguiMatSystemTopPanel == vguiPanel) { //If we're on MatSystemTopPanel, call our drawing code.
		if(g_pEngine->IsDrawingLoadingImage() || !g_pEngine->IsInGame() || !g_pEngine->IsConnected() || g_pEngine->Con_IsVisible() || g_pEngine->IsTakingScreenshot()) {
			return; //We don't want to draw at the menu.
		}
		//This section will be called when the player is not at the menu game and can see the screen or not taking a screenshot.

		inTheMiddle();

		for(int i = 0; i < g_pEntList->GetHighestEntityIndex(); i++) {
			DrawEnemyESP(i);
		}
	}
}

void DoMeAFavour() {
	InitInterfaces();
	FontInit();
	
	CVMTHookManager* hK = new CVMTHookManager;
	if(hK->bInitialize((PDWORD*)g_pIPanel)) {
		//OriginalPaintTraverse = (PaintTraverseFn)hK->dwHookMethod((DWORD)pt, 41);
	}

	CVMTHookManager* testHook = new CVMTHookManager;
	char buff[1024] = {0};
	std::ofstream fDebug;
	fDebug.open("__debug.txt", std::fstream::app);
	testHook->bInitialize((PDWORD*)g_pEngine);
	for (int i = 0; i < testHook->iGetFuncCount(); i++)
	{
		sprintf_s(buff, "function%03d --> engine.dll+%x", i, testHook->dwGetMethodAddress(i) - (DWORD)hEngine);
		fDebug << buff << std::endl;
	}
	fDebug.close();

	sprintf_s(buff, "g_pSurface: %p\ng_pIPanel: %p\ng_pEntListn: %p\ng_pEngine: %p", g_pSurface, g_pIPanel, g_pEntList, g_pEngine);
	MessageBoxA(NULL, buff, "", MB_OK);
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD  reason, LPVOID lpReserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(handle);
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DoMeAFavour, NULL, 0, NULL);
			break;
	}
	return TRUE;
}