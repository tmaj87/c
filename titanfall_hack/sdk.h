#pragma once
#include "vector.h"

inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}

typedef unsigned int VPANEL;
typedef float matrix3x4[3][4];

typedef struct player_info_s {
	char    _0x0000[0x0008];    // 0x0000
	char    szName[32];            // 0x0008
	char    _0x0028[0x0228];    // 0x0028
} player_info_t;

typedef void* (__cdecl* tCreateInterface)(const char*, int*);
typedef double(__cdecl* tPlat_FloatTime)();
typedef void* (__thiscall* tPaintTraverse)(void*, VPANEL, bool, bool);

const DWORD64 m_iHealth = 0x1B8;
const DWORD64 m_iTeamNum = 0x1D0;
//const DWORD64 m_localAngle = 0x1FC;
const DWORD64 m_localOrigin = 0x208;
const DWORD64 m_iMaxHealth = 0x324;
const DWORD64 m_lifeState = 0x488;
//
const DWORD64 m_inventory = 0x23D0;
const DWORD64 m_hGroundEntity = 0x1B4;
//const DWORD64 m_duckState = 0x2D14;
//const DWORD64 m_title = 0x2464;

class ClientClass
{
public:
	const char* GetName()
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 1)(this);
	}
};

//class CViewSetup;

class IBaseClientDLL
{
public:
	/*
	bool GetPlayerView(CViewSetup& playerView)
	{
	typedef bool(__thiscall* OriginalFn)(PVOID, CViewSetup&);
	return getvfunc<OriginalFn>(this, 74)(this, playerView);
	}
	*/
};

class CViewRender {
public:
	matrix3x4* GetWorldToScreenMatrix(bool bUnknown = false)
	{
		typedef matrix3x4* (__thiscall* OriginalFn)(PVOID, bool);
		return getvfunc<OriginalFn>(this, 13)(this, bUnknown);
	}
};

class IClientRenderable;

class CBaseEntity
{
public:
	bool IsDormant() // ???
	{
		PVOID pNetworkable = (PVOID)(this + 0x10); // 0x10
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 8)(pNetworkable);
	}
	int GetIndex() // ???
	{
		PVOID pNetworkable = (PVOID)(this + 0x10);
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 9)(pNetworkable);
	}
	ClientClass* GetClientClass() // ???
	{
		PVOID pNetworkable = (PVOID)(this + 0x10);
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}
	Vector& GetAbsOrigin()
	{
		typedef Vector& (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 9)(this);
	}
	bool SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		PVOID pRenderable = (PVOID)(this + 0x8);
		typedef bool(__thiscall* OriginalFn)(PVOID, matrix3x4*, int, int, float);
		return getvfunc<OriginalFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
};





struct Ray_t
{
	__declspec(align(16)) Vector m_Start;
	__declspec(align(16)) Vector m_Delta;
	__declspec(align(16)) Vector m_StartOffset;
	__declspec(align(16)) Vector m_Extents;

	//const   matrix3x4_t* m_pWorldAxisTransform;

	bool    m_IsRay;
	bool    m_IsSwept;

	//Ray_t() : m_pWorldAxisTransform(NULL) { }

	void Init(Vector& vecStart, Vector& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		//m_pWorldAxisTransform = NULL;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}
};


struct cplane_t
{
	Vector  normal;
	float   dist;
	BYTE    type;
	BYTE    signbits;
	BYTE    pad[2];
};

class CBaseTrace
{
public:
	Vector                  startpos;
	Vector                  endpos;
	cplane_t                plane;
	float                   fraction;
	int                             contents;
	unsigned short  dispFlags;
	bool                    allsolid;
	bool                    startsolid;
};

struct csurface_t
{
	const char*             name;
	short                   surfaceProps;
	unsigned short  flags;
};

class CGameTrace : public CBaseTrace
{
public:
	bool                    DidHitWorld() const;
	bool                    DidHitNonWorldEntity() const;
	int                             GetEntityIndex() const;
	bool                    DidHit() const;
public:
	float                   fractionleftsolid;
	csurface_t              surface;
	int                             hitgroup;
	short                   physicsbone;
	unsigned short  worldSurfaceIndex;
	CBaseEntity*               m_pEnt;
	int                             hitbox;
};

inline bool CGameTrace::DidHit() const
{
	return fraction < 1.0f || allsolid || startsolid;
}

typedef CGameTrace trace_t;

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class ITraceFilter
{
public:
	virtual bool            ShouldHitEntity(PVOID pEntity, int contentsMask) = 0;
	virtual TraceType_t     GetTraceType() const = 0;
};

class EngineTraceClient004
{
public:
	void TraceRay(const Ray_t &ray, unsigned int fMask, void *vNull, trace_t *pTrace)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const Ray_t&, unsigned int, void*, trace_t*);
		getvfunc<OriginalFn>(this, 4)(this, ray, fMask, NULL, pTrace); // 5?
	}
};







class EngineClient
{
public:
	void GetScreenSize(int& wide, int& tall)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		return getvfunc<OriginalFn>(this, 12)(this, wide, tall);
	}
	bool GetPlayerInfo(int ent_num, player_info_t *pinfo)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, int, player_info_t *);
		return getvfunc<OriginalFn>(this, 16)(this, ent_num, pinfo);
	}
	int GetLocalPlayer(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 23)(this);
	}
};

class CEntList
{
public:
	CBaseEntity* GetClientEntity(int entnum)
	{
		typedef CBaseEntity* (__thiscall* OriginalFn)(PVOID, int);
		return getvfunc<OriginalFn>(this, 3)(this, entnum);
	}
	int GetHighestEntityIndex(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 6)(this);
	}
};

class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 14)(this, r, g, b, a);
	}
	void DrawOutlineRectangle(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 19)(this, x0, y0, x1, y1);
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 20)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont(float font)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, float);
		getvfunc<OriginalFn>(this, 26)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 27)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int);
		return getvfunc<OriginalFn>(this, 28)(this, x, y);
	}
	void DrawPrintText(const wchar_t *text, int textLen)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t *, int, int);
		return getvfunc<OriginalFn>(this, 30)(this, text, textLen, 0);
	}
};

class IPanel
{
public:
	void GetPos(VPANEL vguiPanel, int& wide, int& tall)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, VPANEL, int&, int&);
		return getvfunc<OriginalFn>(this, 3)(this, vguiPanel, wide, tall);
	}
	void GetSize(VPANEL vguiPanel, int& wide, int& tall)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, VPANEL, int&, int&);
		return getvfunc<OriginalFn>(this, 5)(this, vguiPanel, wide, tall);
	}
	VPANEL GetParent(VPANEL vguiPanel)
	{
		typedef VPANEL(__thiscall* OriginalFn)(PVOID, VPANEL);
		return getvfunc<OriginalFn>(this, 23)(this, vguiPanel);
	}
	const char* GetName(VPANEL vguiPanel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, VPANEL);
		return getvfunc<OriginalFn>(this, 39)(this, vguiPanel);
	}
};