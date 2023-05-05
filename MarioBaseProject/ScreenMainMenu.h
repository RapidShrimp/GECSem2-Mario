#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include "TextRenderer.h"

class Texture2D;
class TextRenderer;


class ScreenMainMenu : GameScreen
{
public :
	ScreenMainMenu(SDL_Renderer* renderer, GameScreenManager* manager);
	~ScreenMainMenu();
	void Render();
	bool IsSinglePlayer = true;
	inline bool SelectOther() { return !IsSinglePlayer; }
private:
	void Update(float deltaTime, SDL_Event e);
	bool SetupMenu();
	Texture2D* m_background_texture;
	Texture2D* m_character_select;
	TextRenderer* m_SingleplayerText;
	TextRenderer* m_MultiplayerText;
	Vector2D m_background_position;
	SDL_Renderer* m_renderer;
	GameScreenManager* m_screen_manager;
	int m_background_width;
	int m_background_height;
};

