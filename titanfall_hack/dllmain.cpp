#include "header.h"

tPaintTraverse oPaintTraverse;
cvmth64* VMThook;
base* core;
hack* myHack;

bool __DEBUG = 0;
bool MAIN_SWITCH = 0;
bool CROSSHAIR_SWITCH = 1;
bool RADAR_SWITCH = 0;

int myPlayerIdx;
CBaseEntity* myPlayer;

void __fastcall pt(IPanel* pThis, VPANEL vguiPanel, bool bForceRepaint, bool bAllowForce)
{
	oPaintTraverse(pThis, vguiPanel, bForceRepaint, bAllowForce);

	static CBaseEntity* player;
	static Vector playerPos, screenPos;
	static wchar_t buff[512];
	static player_info_s pInfo;
	static float distFromMe;
	// 0 - unused
	// 1 - player
	// 2 - titan
	// 3 - minion
	static byte type;
	static bool enemy;

	static VPANEL mstp = NULL;
	if (mstp == NULL)
	{
		if (!strcmp(pThis->GetName(vguiPanel), "MatSystemTopPanel") && pThis->GetParent(vguiPanel) == 0)
		{
			mstp = vguiPanel;
		}
	}


	static bool once = 1;
	if (GetAsyncKeyState(VK_F5) && once)
	{
		once = 0;
		if (MAIN_SWITCH)
		{
			MAIN_SWITCH = 0;
		}
		else
		{
			MAIN_SWITCH = 1;
		}
	}
	else if (!GetAsyncKeyState(VK_F5) && !once)
	{
		once = 1;
	}


	static bool tripple = 1;
	if (GetAsyncKeyState(VK_F6) && tripple)
	{
		tripple = 0;
		if (RADAR_SWITCH)
		{
			RADAR_SWITCH = 0;
		}
		else
		{
			RADAR_SWITCH = 1;
		}
	}
	else if (!GetAsyncKeyState(VK_F6) && !tripple)
	{
		tripple = 1;
	}

	if (mstp != NULL && SHOW_DEBUG)
	{
		static bool debugged = 1;
		if (!debugged)
		{
			//
			debugged = 1;
		}

		static bool twice = 1;
		if (GetAsyncKeyState(VK_F9) && twice)
		{
			twice = 0;
			if (__DEBUG)
			{
				__DEBUG = 0;
			}
			else
			{
				__DEBUG = 1;
			}
		}
		else if (!GetAsyncKeyState(VK_F9) && !twice)
		{
			twice = 1;
		}
	}

	if (vguiPanel == mstp)
	{
		if (!MAIN_SWITCH)
		{
			myHack->drawOff();
			if (__DEBUG)
			{
				__DEBUG = 0;
			}
			return;
		}

		if (__DEBUG)
		{
			swprintf_s(buff, L"D_eb'ug");
			core->g_pSurface->DrawSetTextFont(0);
			core->g_pSurface->DrawSetTextColor(255, 255, 255, 200);
			core->g_pSurface->DrawSetTextPos(200, 160);
			core->g_pSurface->DrawPrintText(buff, wcslen(buff));
			//
			swprintf_s(buff, L"MAIN_SWITCH: %S", MAIN_SWITCH ? "true" : "false");
			core->g_pSurface->DrawSetTextPos(180, 180);
			core->g_pSurface->DrawPrintText(buff, wcslen(buff));

			swprintf_s(buff, L"radar: %S", RADAR_SWITCH ? "true" : "false");
			core->g_pSurface->DrawSetTextPos(220, 200);
			core->g_pSurface->DrawPrintText(buff, wcslen(buff));

			swprintf_s(buff, L"Stefan Batory");
			core->g_pSurface->DrawSetTextPos(240, 220);
			core->g_pSurface->DrawPrintText(buff, wcslen(buff));
		}

		// about me
		myPlayerIdx = core->g_pEngine->GetLocalPlayer();
		myPlayer = core->g_pEntList->GetClientEntity(myPlayerIdx);
		if (
			myPlayer == NULL
			|| *(int*)(DWORD64(myPlayer) + m_lifeState) != 0
			)
		{
			return;
		}

		if (*(int*)(DWORD64(myPlayer) + m_iMaxHealth) == 5000)
		{
			// EJECT, EJECT, EJECT
		}

		if (CROSSHAIR_SWITCH)
		{
			myHack->inTheMiddle(vguiPanel);
		}

		for (int i = 0; i < core->g_pEntList->GetHighestEntityIndex(); i++)
		{
			player = core->g_pEntList->GetClientEntity(i);

			if (
				player == NULL
				|| i == myPlayerIdx
				|| *(int*)(DWORD64(player) + m_lifeState) != 0
				|| *(int*)(DWORD64(player) + m_iTeamNum) == 0
				|| *(int*)(DWORD64(player) + m_inventory) == 0
				)
			{
				continue;
			}

			type = 1;
			enemy = 1;

			static bool matrixCached = 0;
			if (!matrixCached)
			{
				myHack->getMatrix(); // magic!!
				matrixCached = 1;
			}

			playerPos = player->GetAbsOrigin();
			if (!myHack->w2s(playerPos, screenPos))
			{
				continue;
			}

			distFromMe = myHack->getDist(myPlayer->GetAbsOrigin(), playerPos) / 10;
			if (distFromMe > 500)
			{
				continue;
			}



			// GET CLASS / MODEL NAME??????????????????????
			// GET CLASS / MODEL NAME??????????????????????
			// GET CLASS / MODEL NAME??????????????????????
			core->g_pEngine->GetPlayerInfo(i, &pInfo);
			if (strlen(pInfo.szName) < 6)
			{
				type = 3;
			}

			// set alpha
			int a = 255 - distFromMe / 2;
			if (distFromMe < 400)
			{
				a -= 60;
			}

			if (distFromMe < 120)
			{
				a = 185;
			}

			// get player type
			if (*(int*)(DWORD64(player) + m_iHealth) > 700)
			{
				type = 2;
			}

			// is enemy?
			if (*(int*)(DWORD64(player) + m_iTeamNum) == *(int*)(DWORD64(myPlayer) + m_iTeamNum))
			{
				enemy = 0;
			}

			// set color
			if (enemy)
			{
				core->g_pSurface->DrawSetColor(255, 0, 0, a);
			}
			else
			{
				core->g_pSurface->DrawSetColor(0, 255, 0, 40);
			}


			if (__DEBUG) // main place for finding debug
			{
				/*
				if (myHack->traceray(myPlayer, player) && i < 32)
				{
					swprintf_s(buff, L"visible");
					core->g_pSurface->DrawSetTextFont(0);
					core->g_pSurface->DrawSetTextColor(255, 255, 255, 200);
					core->g_pSurface->DrawSetTextPos(screenPos.x, screenPos.y);
					core->g_pSurface->DrawPrintText(buff, wcslen(buff));
				}
				*/

				swprintf_s(buff, L"index(9):%d  dormant(8):%d", player->GetIndex(), player->IsDormant());
				core->g_pSurface->DrawSetTextFont(0);
				core->g_pSurface->DrawSetTextColor(255, 255, 255, 200);
				core->g_pSurface->DrawSetTextPos(screenPos.x, screenPos.y);
				core->g_pSurface->DrawPrintText(buff, wcslen(buff));
			}

			switch (type)
			{
			case 1: // player
				myHack->drawPlayer(player);
				break;
			case 2: // titan
				if (enemy)
				{
					core->g_pSurface->DrawSetColor(255, 153, 0, a);
				}
				myHack->drawTitan(player);
				break;
			case 3: // minon
				if (!enemy || *(int*)(DWORD64(player) + m_hGroundEntity) == -1) // remove ally and weapons on ground
				{
					continue;
				}
				core->g_pSurface->DrawSetColor(255, 255, 0, a);
				myHack->drawMinion(player);
				break;
			}
			
			if (RADAR_SWITCH && type != 3 && enemy)
			{
				myHack->drawOnRadar(screenPos);
			}
		}
	}
}

void DoMeAFavour()
{
	core = new base();

	VMThook = new cvmth64();
	if (VMThook->bInitialize((PDWORD64*)core->g_pIPanel))
	{
		oPaintTraverse = (tPaintTraverse)VMThook->dwHookMethod((DWORD64)pt, 44);
		myHack = new hack();
	}
	else
	{
		MessageBox(NULL, "error", "", MB_OK);
	}
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD  reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(handle);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DoMeAFavour, NULL, 0, NULL);
		break;
	}
	return 1;
}