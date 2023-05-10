#include "GameScreenOver.h"

GameScreenOver::GameScreenOver(SDL_Renderer* renderer, GameScreenManager* manager, int score) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_manager = manager;
	end_score = score;
	SetupLevel();
}

GameScreenOver::~GameScreenOver()
{
}

bool GameScreenOver::SetupLevel() 
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/SpriteSheet.png"))
	{
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	ScoreDisplay = new TextRenderer(m_renderer);
	if (!ScoreDisplay ->LoadFont("Fonts/PixelFont.ttf", 34, "Score: " + to_string(end_score), {255, 130, 10, 255}))
	{
		cout << "Failed to Load Score Text Font" << endl;
		return false;
	}
	ReturnText = new TextRenderer(m_renderer);
	if (!ReturnText->LoadFont("Fonts/PixelFont.ttf", 15, "Press Enter to Return", { 255, 255, 255, 255 }))
	{
		cout << "Failed to Load Score Text Font" << endl;
		return false;
	}
	return true;
}
void GameScreenOver::Render()
{
	//Title
	SDL_Rect MenuPortion = { 0,0,240,96 };
	SDL_Rect MenuPosition = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT / 2 };

	m_background_texture->Render(MenuPortion, MenuPosition, SDL_FLIP_NONE);
	ScoreDisplay->Render(125, SCREEN_HEIGHT / 2 + 50);
	ReturnText->Render(125, SCREEN_HEIGHT / 2 + 110);

}
void GameScreenOver::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
			m_manager->NextScreen(SCREEN_MENU);
			break;
		}
	}
}


void GameScreenOver::GoToMainMenu()
{
}

