#pragma once

class Settings
{
public:
	//
	// AIMBOT
	//
	bool g_bEnableAimbot = false;
	bool g_bAimbotTeamCheck = false;
	bool g_bAimbotVisibilityCheck = false;
	bool g_bAimbotRCS = false;
	bool g_bAimbotAutoPistols = false;
	bool g_bAimbotNoShotCooldown = false;

	//
	// ESP
	//
	bool g_bEnableESP = false;
	bool g_bESPVisibilityCheck = false;
	bool g_bESPTeamCheck = false;
	bool g_bESPBoxes = false;
	bool g_bESPName = false;
	bool g_bESPWeapon = false;

	//
	// MISC
	//
	bool g_bInfiniteHealth = false;
	bool g_bInfiniteArmor = false;
	bool g_bInfiniteAmmo = false;

	//
	// OTHERS
	//
	bool g_bMenuIsOpen = true;
};
extern Settings g_Settings;