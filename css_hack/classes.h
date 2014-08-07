#ifndef CLASSES_H
#define CLASSES_H

typedef struct player_info_s {
	char name[32];
	int userID;
	char guid[33];
	unsigned long friendsID;
	char friendsName[32];
	bool fakeplayer;
	bool ishltv;
	unsigned long customFiles[4];
	unsigned char filesDownloaded;
} player_info_t;

typedef float matrix3x4[3][4];
//typedef float matrix3x4[4][4]; // haha! nope

enum source_lifestates {
	LIFE_ALIVE,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY,
};

class ISurface
{
public:
	void DrawSetColor( int r, int g, int b, int a )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 11 )( this, r, g, b, a );
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 12 )( this, x0, y0, x1, y1 );
	}
	void DrawOutlinedRect( int x0, int y0, int x1, int y1 )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 14 )( this, x0, y0, x1, y1 );
	}
	void DrawLine( int x0, int y0, int x1, int y1 )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 15 )( this, x0, y0, x1, y1 );
	}
	void DrawSetTextFont(unsigned long font)
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, unsigned long );
		getvfunc<OriginalFn>( this, 17 )( this, font );
	}
	void DrawSetTextColor(int r, int g, int b, int a )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 19 )( this, r, g, b, a );
	}
	void DrawSetTextPos(int x, int y )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int );
		getvfunc<OriginalFn>( this, 20 )( this, x, y );
	}
	void DrawPrintText(const wchar_t *text, int textLen )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, const wchar_t *, int, int );
		return getvfunc<OriginalFn>( this, 22 )( this, text, textLen, 0 );
	}
	unsigned long CreateFont( )
	{
		typedef unsigned int ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 66 )( this );
	}
	void SetFontGlyphSet (unsigned long &font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, unsigned long, const char*, int, int, int, int, int, int, int );
		getvfunc<OriginalFn>( this, 67 )( this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0 );
	}
};

class CBaseEntity
{
public:
	bool IsDormant( )
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( pNetworkable, 8 )( pNetworkable );
	}
	int GetIndex( )
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef int ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( pNetworkable, 9 )( pNetworkable );
	}
	Vector& GetAbsOrigin( )
	{
		typedef Vector& ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>(this, 9)(this);
	}
	bool SetupBones( matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
	{
		PVOID pRenderable = (PVOID)(this + 0x4);
		typedef bool ( __thiscall* OriginalFn )( PVOID, matrix3x4*, int, int, float );
		return getvfunc<OriginalFn>( pRenderable, 16 )( pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime );
	}
};

class EngineClient
{
public:
	float Time( void )
	{
		typedef float ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 14 )( this );
	}
	bool GetPlayerInfo( int ent_num, player_info_t *pinfo )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID, int, player_info_t * );
		return getvfunc<OriginalFn>(this, 8)(this, ent_num, pinfo );
	}
	int GetLocalPlayer( void )
	{
		typedef int ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 12 )( this );
	}
	const matrix3x4& WorldToScreenMatrix( void )
	{
		typedef const matrix3x4& ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 36 )(this);
	}
	bool IsTakingScreenshot( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 85 )( this );
	}
	bool Con_IsVisible( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 11 )( this );
	}
	bool IsConnected( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 27 )( this );
	}
	void GetScreenSize( int& width, int& height )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int& , int& );
		return getvfunc<OriginalFn>( this, 5 )( this, width, height );
	}
	bool IsInGame( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 26 )( this );
	}
	bool IsDrawingLoadingImage( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 28 )( this );
	}
};


class CEntList
{
public:
	CBaseEntity* GetClientEntity( int entnum )
	{
		typedef CBaseEntity* ( __thiscall* OriginalFn )( PVOID, int );
		return getvfunc<OriginalFn>( this, 3 )( this, entnum );
	}
	int GetHighestEntityIndex(void)
	{
		typedef int ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 6 )( this );
	}
};

class IPanel
{
public:
	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char* ( __thiscall* OriginalFn )( PVOID, unsigned int );
		return getvfunc<OriginalFn>( this, 36 )( this, vguiPanel );
	}
};

#endif