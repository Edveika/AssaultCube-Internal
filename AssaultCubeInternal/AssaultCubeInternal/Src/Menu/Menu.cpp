#include "../Includes.h"

int tab = 0;
float menuX = 200;
float menuY = 200;

void Menu::Controls()
{
	//
	// Menu's movement logic
	//
	if (GetAsyncKeyState('I'))
		--menuY;
	else if (GetAsyncKeyState('K'))
		++menuY;
	else if (GetAsyncKeyState('J'))
		--menuX;
	else if (GetAsyncKeyState('L'))
		++menuX;

	//
	// Menu's tab switch logic
	//
	if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F1))
		tab = AIMBOT;
	else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F2))
		tab = VISUALS;
	else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F3))
		tab = MISC;
}

void Menu::Render(GL::Font font)
{
	// Draw the main body thing
	GL::DrawFilledRect(menuX, menuY, 200, 320, Colors::white);

	// Draw the second body thing...
	GL::DrawFilledRect(menuX + 10, menuY + 10, 180, 300, Colors::gray);

	if (tab == AIMBOT)
	{
		if (GetAsyncKeyState(VK_F1) & 5)
			g_Settings.g_bEnableAimbot = !g_Settings.g_bEnableAimbot;

		if (g_Settings.g_bEnableAimbot)
			font.Print(menuX + 20, menuY + 20 + FONT_WIDTH, Colors::green, "%s", "Enable aimbot - F1");
		else
			font.Print(menuX + 20, menuY + 20 + FONT_WIDTH, Colors::red, "%s", "Enable aimbot - F1");

		if (GetAsyncKeyState(VK_F2) & 5)
			g_Settings.g_bAimbotTeamCheck = !g_Settings.g_bAimbotTeamCheck;

		if (g_Settings.g_bAimbotTeamCheck)
			font.Print(menuX + 20, menuY + 34 + FONT_WIDTH, Colors::green, "%s", "Team check - F2");
		else
			font.Print(menuX + 20, menuY + 34 + FONT_WIDTH, Colors::red, "%s", "Team check - F2");
		
		if (GetAsyncKeyState(VK_F3) & 5)
			g_Settings.g_bAimbotVisibilityCheck = !g_Settings.g_bAimbotVisibilityCheck;

		if (g_Settings.g_bAimbotVisibilityCheck)
			font.Print(menuX + 20, menuY + 47 + FONT_WIDTH, Colors::green, "%s", "Visibility check - F3");
		else
			font.Print(menuX + 20, menuY + 47 + FONT_WIDTH, Colors::red, "%s", "Visibility check - F3");

		if (GetAsyncKeyState(VK_F4) & 5)
			g_Settings.g_bAimbotRCS = !g_Settings.g_bAimbotRCS;

		if (g_Settings.g_bAimbotRCS)
			font.Print(menuX + 20, menuY + 61 + FONT_WIDTH, Colors::green, "%s", "Anti-recoil - F4");
		else
			font.Print(menuX + 20, menuY + 61 + FONT_WIDTH, Colors::red, "%s", "Anti-recoil - F4");

		if (GetAsyncKeyState(VK_F5) & 5)
			g_Settings.g_bAimbotNoShotCooldown = !g_Settings.g_bAimbotNoShotCooldown;

		if (g_Settings.g_bAimbotNoShotCooldown)
			font.Print(menuX + 20, menuY + 75 + FONT_WIDTH, Colors::green, "%s", "No shot cooldown - F5");
		else
			font.Print(menuX + 20, menuY + 75 + FONT_WIDTH, Colors::red, "%s", "No shot cooldown - F5");

		if (GetAsyncKeyState(VK_F6) & 5)
			g_Settings.g_bAimbotAutoPistols = !g_Settings.g_bAimbotAutoPistols;

		if (g_Settings.g_bAimbotAutoPistols)
			font.Print(menuX + 20, menuY + 89 + FONT_WIDTH, Colors::green, "%s", "Auto pistols - F6");
		else
			font.Print(menuX + 20, menuY + 89 + FONT_WIDTH, Colors::red, "%s", "Auto pistols - F6");
	}
	else if (tab == VISUALS)
	{
		if (GetAsyncKeyState(VK_F1) & 5)
			g_Settings.g_bEnableESP = !g_Settings.g_bEnableESP;

		if (g_Settings.g_bEnableESP)
			font.Print(menuX + 20, menuY + 20 + FONT_WIDTH, Colors::green, "%s", "Enable ESP - F1");
		else
			font.Print(menuX + 20, menuY + 20 + FONT_WIDTH, Colors::red, "%s", "Enable ESP - F1");

		if (GetAsyncKeyState(VK_F2) & 5)
			g_Settings.g_bESPBoxes = !g_Settings.g_bESPBoxes;

		if (g_Settings.g_bESPBoxes)
			font.Print(menuX + 20, menuY + 34 + FONT_WIDTH, Colors::green, "%s", "Enable box - F2");
		else
			font.Print(menuX + 20, menuY + 34 + FONT_WIDTH, Colors::red, "%s", "Enable box - F2");

		if (GetAsyncKeyState(VK_F3) & 5)
			g_Settings.g_bESPName = !g_Settings.g_bESPName;

		if (g_Settings.g_bESPName)
			font.Print(menuX + 20, menuY + 47 + FONT_WIDTH, Colors::green, "%s", "Enable name - F3");
		else
			font.Print(menuX + 20, menuY + 47 + FONT_WIDTH, Colors::red, "%s", "Enable name - F3");

		if (GetAsyncKeyState(VK_F4) & 5)
			g_Settings.g_bESPWeapon = !g_Settings.g_bESPWeapon;

		if (g_Settings.g_bESPWeapon)
			font.Print(menuX + 20, menuY + 61 + FONT_WIDTH, Colors::green, "%s", "Enable weapon - F4");
		else
			font.Print(menuX + 20, menuY + 61 + FONT_WIDTH, Colors::red, "%s", "Enable weapon - F4");

		if (GetAsyncKeyState(VK_F5) & 5)
			g_Settings.g_bESPTeamCheck = !g_Settings.g_bESPTeamCheck;

		if (g_Settings.g_bESPTeamCheck)
			font.Print(menuX + 20, menuY + 75 + FONT_WIDTH, Colors::green, "%s", "Team check - F5");
		else
			font.Print(menuX + 20, menuY + 75 + FONT_WIDTH, Colors::red, "%s", "Team check - F5");

		if (GetAsyncKeyState(VK_F6) & 5)
			g_Settings.g_bESPVisibilityCheck = !g_Settings.g_bESPVisibilityCheck;

		if (g_Settings.g_bESPVisibilityCheck)
			font.Print(menuX + 20, menuY + 89 + FONT_WIDTH, Colors::green, "%s", "Visibility check - F6");
		else
			font.Print(menuX + 20, menuY + 89 + FONT_WIDTH, Colors::red, "%s", "Visibility check - F6");
	}
	else if (tab == MISC)
	{
		if (GetAsyncKeyState(VK_F1) & 5)
			g_Settings.g_bInfiniteHealth = !g_Settings.g_bInfiniteHealth;

		if (g_Settings.g_bInfiniteHealth)
			font.Print(menuX + 20, menuY + 20 + FONT_WIDTH, Colors::green, "%s", "Infinite health - F1");
		else
			font.Print(menuX + 20, menuY + 20 + FONT_WIDTH, Colors::red, "%s", "Infinite health - F1");

		if (GetAsyncKeyState(VK_F2) & 5)
			g_Settings.g_bInfiniteArmor = !g_Settings.g_bInfiniteArmor;

		if (g_Settings.g_bInfiniteArmor)
			font.Print(menuX + 20, menuY + 34 + FONT_WIDTH, Colors::green, "%s", "Infinite armor - F2");
		else
			font.Print(menuX + 20, menuY + 34 + FONT_WIDTH, Colors::red, "%s", "Infinite armor - F2");

		if (GetAsyncKeyState(VK_F3) & 5)
			g_Settings.g_bInfiniteAmmo = !g_Settings.g_bInfiniteAmmo;

		if (g_Settings.g_bInfiniteAmmo)
			font.Print(menuX + 20, menuY + 47 + FONT_WIDTH, Colors::green, "%s", "Infinite ammo - F3");
		else
			font.Print(menuX + 20, menuY + 47 + FONT_WIDTH, Colors::red, "%s", "Infinite ammo - F3");
	}
}