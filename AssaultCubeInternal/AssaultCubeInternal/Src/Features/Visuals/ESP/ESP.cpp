#include "../../../Includes.h"

bool ESP::IsTeamGame()
{
	if ((*gameMode == 0 || *gameMode == 4 || *gameMode == 5 || *gameMode == 7 || *gameMode == 11 || *gameMode == 13 || *gameMode == 14 || *gameMode == 16 || *gameMode == 17 || *gameMode == 20 || *gameMode == 21))
		return true;
	else
		return false;
}

bool ESP::IsEnemy(Entity* entity)
{
	if (pLocalPlayer->Team == entity->Team)
		return false;
	else
		return true;
}

void ESP::DrawESPBox(Entity* entity, Vector2 screen, GL::Font& font)
{
	const GLubyte* color = nullptr;

	if (g_Settings.g_bESPTeamCheck && !IsEnemy(entity))
		return;

	if (g_Settings.g_bESPVisibilityCheck && !IsVisible(entity))
		return;

	if (IsTeamGame() && !IsEnemy(entity))
		color = Colors::green;
	else
		color = Colors::red;

	float distance = pLocalPlayer->Coordinates.Distance(entity->Coordinates);

	float scale = (GAME_UNIT / distance) * (viewport[2] / VIRTUAL_SCREEN_WIDTH);
	float x = screen.x - scale;
	float y = screen.y - scale * PLAYER_ASPECT_RATIO;
	float width = scale * 2;
	float height = scale * PLAYER_ASPECT_RATIO * 2;

	GL::DrawOutline(x, y, width, height, 3.0f, color);
}

void ESP::DrawName(Entity* entity, Vector2 screen, GL::Font& font)
{
	const GLubyte* color = nullptr;

	if (g_Settings.g_bESPTeamCheck && !IsEnemy(entity))
		return;

	if (g_Settings.g_bESPVisibilityCheck && !IsVisible(entity))
		return;

	if (IsTeamGame() && !IsEnemy(entity))
		color = Colors::green;
	else
		color = Colors::red;

	float distance = pLocalPlayer->Coordinates.Distance(entity->Coordinates);

	float scale = (GAME_UNIT / distance) * (viewport[2] / VIRTUAL_SCREEN_WIDTH);
	float x = screen.x - scale;
	float y = screen.y - scale * PLAYER_ASPECT_RATIO;
	float width = scale * 2;
	float height = scale * PLAYER_ASPECT_RATIO * 2;

	float nameX = font.CenterText(x, width, strlen(entity->Name) * ESP_FONT_WIDTH);
	float nameY = y - ESP_FONT_HEIGHT / 2;

	font.Print(nameX, nameY, color, "%s", entity->Name);
}

void ESP::DrawWeapon(Entity* entity, Vector2 screen, GL::Font& font)
{
	const GLubyte* color = nullptr;

	if (g_Settings.g_bESPTeamCheck && !IsEnemy(entity))
		return;

	if (g_Settings.g_bESPVisibilityCheck && !IsVisible(entity))
		return;

	if (IsTeamGame() && !IsEnemy(entity))
		color = Colors::green;
	else
		color = Colors::red;

	float distance = pLocalPlayer->Coordinates.Distance(entity->Coordinates);

	float scale = (GAME_UNIT / distance) * (viewport[2] / VIRTUAL_SCREEN_WIDTH);
	float x = screen.x - scale;
	float y = screen.y + scale * PLAYER_ASPECT_RATIO;
	float width = scale * 2;
	float height = scale * PLAYER_ASPECT_RATIO * 2;

	float weaponX = font.CenterText(x, width, strlen(entity->CurrentWeapon->Stats->Name) * ESP_FONT_WIDTH);
	float weaponY = (y + ESP_FONT_HEIGHT / 2) + 5;

	font.Print(weaponX, weaponY, color, "%s", entity->CurrentWeapon->Stats->Name);
}

void ESP::DrawHealth(Entity* entity, Vector2 screen, GL::Font& font)
{

}

void ESP::DrawArmor(Entity* entity, Vector2 screen, GL::Font& font)
{

}

void ESP::Draw(GL::Font& font)
{
	glGetIntegerv(GL_VIEWPORT, viewport);

	for (int i = 0; i < (*playerCount); i++)
	{
		// Current entity
		Entity* entity = entityList->entity[i];
		
		if (entity)
		{
			Vector3 center = entity->HeadPos;
			center.z = center.z - EYE_HEIGHT + PLAYER_HEIGHT / 2;

			Vector2 screenPos;

			if (entityList && entity && IsValidEntity(entity) && IsValidEntity(entity) && entity->Health > 0 && Math::WorldToScreen(center, screenPos, viewMatrix, viewport[2], viewport[3]))
			{
				if (g_Settings.g_bESPBoxes)
					DrawESPBox(entity, screenPos, font);

				if (g_Settings.g_bESPName)
					DrawName(entity, screenPos, font);

				if (g_Settings.g_bESPWeapon)
					DrawWeapon(entity, screenPos, font);
			}
		}
	}
}