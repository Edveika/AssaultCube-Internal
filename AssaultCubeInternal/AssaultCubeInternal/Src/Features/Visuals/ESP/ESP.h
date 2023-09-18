#pragma once

// Scalling
// Diffrent on every game. Must change it so the boxes scale properly.
const int VIRTUAL_SCREEN_WIDTH = 800;
const int GAME_UNIT = 400;

const float PLAYER_HEIGHT = 5.25f;
const float PLAYER_WIDTH = 2.0f;
const float EYE_HEIGHT = 4.5f;

const float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;

// The height and width of CONSOLAS characters font
const int ESP_FONT_HEIGHT = 15;
const int ESP_FONT_WIDTH = 9;

class ESP
{
public:
	int viewport[4];
	int* gameMode = (int*)(0x50F49C);
	float *viewMatrix = (float*)(0x501AE8);

	bool IsTeamGame();
	bool IsEnemy(Entity* entity);
	
	void DrawESPBox(Entity* entity, Vector2 screen, GL::Font& font);
	void DrawName(Entity* entity, Vector2 screen, GL::Font& font);
	void DrawWeapon(Entity* entity, Vector2 screen, GL::Font& font);
	void DrawHealth(Entity* entity, Vector2 screen, GL::Font& font);
	void DrawArmor(Entity* entity, Vector2 screen, GL::Font& font);
	void Draw(GL::Font& font);
};