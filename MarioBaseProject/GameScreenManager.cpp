#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_CurrentScreen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() 
{
	m_renderer = nullptr;
	delete m_CurrentScreen;
	m_CurrentScreen = nullptr;
}

void GameScreenManager::Render()
{
	m_CurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_CurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	if (m_CurrentScreen != nullptr) 
	{
		delete m_CurrentScreen;
	}
	GameScreenLevel1* tempScreen;
	switch (new_screen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_CurrentScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}
