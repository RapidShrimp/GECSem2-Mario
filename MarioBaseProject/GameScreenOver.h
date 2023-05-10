#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include "TextRenderer.h"
#include "Constants.h"

class Texture2D;
class TextRenderer;

class GameScreenOver : GameScreen
{
public:
	GameScreenOver(SDL_Renderer* renderer, GameScreenManager* manager, int score);
	~GameScreenOver();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	void GoToMainMenu();

private:
	bool SetupLevel();
	Texture2D* m_background_texture;
	SDL_Renderer* m_renderer;
	GameScreenManager* m_manager;
	TextRenderer* ScoreDisplay;
	TextRenderer* ReturnText;
	int end_score;
};

