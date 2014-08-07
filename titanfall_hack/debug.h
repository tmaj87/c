#pragma once
#include <fstream>

using namespace std;

class dbg
{
private:
	ofstream handle;
	char *name;
public:
	dbg()
	{
		name = "__debug.txt";
	}
	void cleanFile()
	{
		handle.open(name, fstream::trunc);
		handle.close();
	}
	void toFile(const char* str)
	{
		handle.open(name, fstream::app);
		handle << str << endl;
		handle.close();
	}
};


/*
headBone = Vector(boneList[10][0][3], boneList[10][1][3], boneList[10][2][3]);
for (int i = 11; i < 15; i++)
{
if (boneList[i][2][3] > headBone.z)
{
headBone = Vector(boneList[i][0][3], boneList[i][1][3], boneList[i][2][3]);
}
}
*/

/*
char buff[512] = { 0 };
//sprintf_s(buff, "hEngine: %p\nhClient: %p\nhVGui: %p\nhVGui2: %p\n", hEngine, hClient, hVGui, hVGui2);
//DebugToFile(buff);
//sprintf_s(buff, "g_pEngineFactory: %p\ng_ClientFactory: %p\ng_VGUIFactory: %p\ng_VGUI2Factory: %p\n", g_pEngineFactory, g_ClientFactory, g_VGUIFactory, g_VGUI2Factory);
//DebugToFile(buff);
sprintf_s(buff, "g_pEngine: %p\ng_pEntList: %p\ng_pSurface: %p\ng_pIPanel: %p\ng_pClient: %p\n", g_pEngine, g_pEntList, g_pSurface, g_pIPanel, g_pClient, engineTrace);
debug->toFile(buff);
*/