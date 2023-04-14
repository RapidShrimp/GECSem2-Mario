#pragma once
#include "GameScreen.h"
#include "Texture2D.h"
class Texture2D;

class ScreenMainMenu : GameScreen
{
public :
	ScreenMainMenu(SDL_Renderer* renderer);
	~ScreenMainMenu();
	void Render();
private:
	bool SetupMenu();
	Texture2D* m_background_texture;
	SDL_Renderer* m_renderer;
};

