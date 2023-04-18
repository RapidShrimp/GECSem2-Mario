#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
class Texture2D;

class ScreenMainMenu : GameScreen
{
public :
	ScreenMainMenu(SDL_Renderer* renderer, GameScreenManager* manager);
	~ScreenMainMenu();
	void Render();
private:
	void Update(float deltaTime, SDL_Event e);
	bool SetupMenu();
	Texture2D* m_background_texture;
	Vector2D m_background_position;
	SDL_Renderer* m_renderer;
	GameScreenManager* m_screen_manager;
	int m_background_width;
	int m_background_height;
};

