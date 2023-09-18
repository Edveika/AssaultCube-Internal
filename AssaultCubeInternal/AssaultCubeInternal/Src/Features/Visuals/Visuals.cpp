#include "../../Includes.h"

ESP esp;
GL::Font glFont;

void Visuals::Draw()
{
	HDC currentHDC = wglGetCurrentDC(); // Get current DC every frame

	// If the font is not build, we need to build it in the context of currentHDC or it will not work.
	// If current hdc doesnt match the old one, means dedvice context has changed. Ex: you went from singleplayer to multiplayer & it changed the device context. Then the font only applied to the priev. one & not current one.(Not a common problem)  
	if (!glFont.bBuilt || currentHDC != glFont.hdc)
		// Build font
		glFont.Build(FONT_HEIGHT);

	// Setup orthographic matrix
	GL::SetupOrtho();

	if (g_Settings.g_bEnableESP)
		esp.Draw(glFont); // Draw the ESP

	if (g_Settings.g_bMenuIsOpen)
		Menu::Render(glFont); // Render the menu

	// Restore that matrix thing
	GL::RestoreGL();
}