#ifndef SDK_H
#define SDK_H

inline void**& getvtable( void* inst, size_t offset = 0 )
{
	return *reinterpret_cast<void***>( (size_t)inst + offset );
}
inline const void** getvtable( const void* inst, size_t offset = 0 )
{
	return *reinterpret_cast<const void***>( (size_t)inst + offset );
}
template< typename Fn >
inline Fn getvfunc( const void* inst, size_t index, size_t offset = 0 )
{
	return reinterpret_cast<Fn>( getvtable( inst, offset )[ index ] );
}

typedef void* ( __cdecl* CreateInterface_t )(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
typedef void* ( __thiscall* PaintTraverseFn )( void*, unsigned int, bool, bool );
PaintTraverseFn OriginalPaintTraverse;

#include "vector.h"
#include "classes.h"

HMODULE hEngine = NULL;
HMODULE hClient = NULL;
HMODULE hVGui = NULL;
HMODULE hVGui2 = NULL;

CreateInterface_t g_pEngineFactory = NULL;
CreateInterface_t g_ClientFactory = NULL;
CreateInterface_t g_VGUIFactory = NULL;
CreateInterface_t g_VGUI2Factory = NULL;

EngineClient* g_pEngine;
CEntList* g_pEntList;
ISurface* g_pSurface;
IPanel* g_pIPanel;

unsigned long drawFont;

void InitInterfaces() {
	// wait till modules load
	while (hEngine == NULL) {
		hEngine = GetModuleHandle("engine.dll");
		Sleep(100);
	}
	while (hClient == NULL) {
		hClient = GetModuleHandle("client.dll");
		Sleep(100);
	}
	while (hVGui == NULL) {
		hVGui = GetModuleHandle("vguimatsurface.dll");
		Sleep(100);
	}
	while (hVGui2 == NULL) {
		hVGui2 = GetModuleHandle("vgui2.dll");
		Sleep(100);
	}

	// funny way of doing this
	g_pEngineFactory = (CreateInterfaceFn)GetProcAddress(hEngine, "CreateInterface");
	g_ClientFactory = (CreateInterfaceFn)GetProcAddress(hClient, "CreateInterface");
	g_VGUIFactory = (CreateInterfaceFn)GetProcAddress(hVGui, "CreateInterface");
	g_VGUI2Factory = (CreateInterfaceFn)GetProcAddress(hVGui2, "CreateInterface");
	
	// ...
	g_pEngine = (EngineClient*)g_pEngineFactory("VEngineClient013", NULL);
	g_pEntList = (CEntList*)g_ClientFactory("VClientEntityList003", NULL);
	g_pSurface = (ISurface*)g_VGUIFactory("VGUI_Surface030", NULL);
	g_pIPanel = (IPanel*)g_VGUI2Factory("VGUI_Panel009", NULL);
}

void FontInit() {
	drawFont = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(drawFont, "Arial", 13, 500, 0, 0, 0x200);
}

#endif