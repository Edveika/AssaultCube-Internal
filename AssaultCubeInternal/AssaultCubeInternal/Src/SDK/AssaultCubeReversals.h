#pragma once
#include "Math/Math.h"

enum gameModes
{
	TEAMDEATHMATCH = 0,
	COOPEDIT,
	DEATHMATCH,
	SURVIVOR,
	TEAMSURVIVOR,
	CTF,
	PISTOLFRENZY,
	BOTTEAMDEATHMATCH,
	BOTDEATHMATCH,
	LASTSWISSSTANDING,
	ONESHOTONEKILL,
	TEAMONESHOTONEKILL,
	BOTONESHOTONEKILL,
	HUNTTHEFLAG,
	TEAMKEEPTHEFLAG,
	KEEPTHEFLAG,
	TEAMPF,
	TEAMLSS,
	BOTPISTOLFRENZY,
	BOtlSS,
	BOTTEAMSURVIVOR,
	BOTTEAMONESHOTONEKILL,
	NUM
};

// Entity structure
class Entity
{
public:
	int32_t VTable; //0x0000
	Vector3 HeadPos; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 Coordinates; //0x0034
	Vector3 ViewAngles; //0x0040
	char pad_004C[4]; //0x004C
	float N0000005D; //0x0050
	char pad_0054[4]; //0x0054
	float N0000005F; //0x0058
	float N00000060; //0x005C
	float N00000061; //0x0060
	char pad_0064[30]; //0x0064
	int8_t NoClip; //0x0082
	int8_t Invisibility; //0x0083
	char pad_0084[116]; //0x0084
	int32_t Health; //0x00F8
	int32_t Armor; //0x00FC
	char pad_0100[20]; //0x0100
	int32_t PistolAmmo; //0x0114
	int32_t CarbineAmmo; //0x0118
	int32_t ShotgunAmmo; //0x011C
	int32_t SubGunAmmo; //0x0120
	int32_t SniperAmmo; //0x0124
	int32_t AssaultRifleAmmo; //0x0128
	char pad_012C[8]; //0x012C
	int32_t DualPistolsAmmo; //0x0134
	char pad_0138[4]; //0x0138
	int32_t PistolMagAmmo; //0x013C
	int32_t CarbineMagAmmo; //0x0140
	int32_t ShotgunMagAmmo; //0x0144
	int32_t SubGunMagAmmo; //0x0148
	int32_t SniperMagAmmo; //0x014C
	int32_t AssaultRifleMagAmmo; //0x0150
	char pad_0154[4]; //0x0154
	int32_t Grenade; //0x0158
	int32_t DualPistolMagAmmo; //0x015C
	char pad_0160[16]; //0x0160
	int32_t WeaponCooldown; //0x0170
	char pad_0174[4]; //0x0174
	int32_t AssaultRifleCooldown; //0x0178
	char pad_017C[36]; //0x017C
	int32_t AssaultRifleShotCount; //0x01A0
	char pad_01A4[128]; //0x01A4
	bool bAttack; //0x0224
	char Name[16]; //0x0225
	char pad_0235[247]; //0x0235
	int8_t Team; //0x032C
	char pad_032D[11]; //0x032D
	int8_t Spectate; //0x0338
	char pad_0339[59]; //0x0339
	class Weapon* CurrentWeapon; //0x0374
	char pad_0378[3324]; //0x0378
}; //Size: 0x1074
static_assert(sizeof(Entity) == 0x1074);

//Weapon structure
class Weapon
{
public:
	char pad_0000[12]; //0x0000
	class WeaponStats* Stats; //0x000C
	char pad_0010[4]; //0x0010
	class AmmoInClip* Ammo; //0x0014
}; //Size: 0x0018
static_assert(sizeof(Weapon) == 0x18);

// Current weapon ammo structure
class AmmoInClip
{
public:
	int32_t Ammo; //0x0000
}; //Size: 0x0004
static_assert(sizeof(AmmoInClip) == 0x4);

// Weapon settings structure
class WeaponStats
{
public:
	char Name[16]; //0x0000
	char pad_0010[248]; //0x0010
	int16_t ReloadCooldown; //0x0108
	int16_t Cooldown; //0x010A
	int16_t Damage; //0x010C
	char pad_010E[10]; //0x010E
	int16_t MagSize; //0x0118
	char pad_011A[6]; //0x011A
	int16_t RecoilX; //0x0120
	int16_t RecoilY; //0x0122
	char pad_0124[4]; //0x0124
	int16_t IsAutomatic; //0x0128
	char pad_012A[220]; //0x012A
}; //Size: 0x0206
static_assert(sizeof(WeaponStats) == 0x206);

// Entity list structure
struct EntityList
{
	Entity* entity[31];
};

// Module base, duh
inline DWORD moduleBase = (DWORD)GetModuleHandle(L"ac_client.exe");

// Ptr to local player object
inline Entity* pLocalPlayer;

// Ptr to entity list
inline EntityList* entityList;

// Player count
inline int* playerCount;

// SDL cursor
typedef int (__cdecl* _SDLShowCursor)(int visibility);
inline _SDLShowCursor SDLShowCursor = (_SDLShowCursor)(0x49E532);

// Console log
typedef void(__cdecl* _ChatLog)(char* message, ...);
inline _ChatLog ChatLog = (_ChatLog)(0x46B060);

// Kill mesage log thing
typedef void(__thiscall* _GuiLog)(char* message);
inline _GuiLog GuiLog = (_GuiLog)(0x408E80);

// Kill message + console message log
typedef void(__cdecl* _Log)(char* message);
inline _Log Log = (_Log)(0x4090F0);

// Checks if the entity is valid. Kewl.
inline bool IsValidEntity(Entity* entity)
{
	if (entity)
	{
		if (entity->VTable == 0x4E4A98 || entity->VTable == 0x4E4AC0)
		{
			return true;
		}
	}
	return false;
}

struct traceresult_s
{
	Vector3 end;
	bool collided;
};

inline bool IsVisible(Entity* entity)
{
	DWORD traceLine = 0x48A310;
	traceresult_s traceresult;
	traceresult.collided = false;
	Vector3 from = pLocalPlayer->HeadPos;
	Vector3 to = entity->HeadPos;

	__asm
	{
		push 0; bSkipTags
		push 0; bCheckPlayers
		push pLocalPlayer
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [traceresult]
		call traceLine;
		add esp, 36
	}
	return !traceresult.collided;
}