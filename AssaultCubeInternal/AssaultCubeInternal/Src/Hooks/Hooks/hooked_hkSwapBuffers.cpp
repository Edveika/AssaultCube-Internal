#include "../../Includes.h"

BOOL __stdcall Hooks::hkwglSwapBuffers(HDC hDc)
{
	// Menu toggle
	if (GetAsyncKeyState(VK_INSERT) & 5)
		g_Settings.g_bMenuIsOpen = !g_Settings.g_bMenuIsOpen;

	// Get entity base address
	pLocalPlayer = *(Entity**)(moduleBase + 0x10F4F4);

	// Get entity list address
	entityList = *(EntityList**)0x50F4F8;

	// Get player count value
	playerCount = (int*)(0x50f500);

	// Check if the local player ptr is not null
	if (pLocalPlayer != NULL)
	{
		if (g_Settings.g_bEnableAimbot)
			Aimbot::Run();

		if (g_Settings.g_bInfiniteHealth)
			Misc::InfiniteHealth();

		if (g_Settings.g_bInfiniteArmor)
			Misc::InfiniteArmor();

		if (g_Settings.g_bInfiniteAmmo)
			Misc::InfiniteAmmo();
	}

	// Menu movement controls etc 
	Menu::Controls();

	// Draw visuals
	Visuals::Draw();

	// Return the gateway (continue the execution of the original function)
	return wglSwapBuffersGateway(hDc);
}
