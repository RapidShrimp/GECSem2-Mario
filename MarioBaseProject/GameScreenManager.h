#pragma once
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H
#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* m_renderer;
	GameScreen* m_CurrentScreen;
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();
	bool m_singleplayer;
	void Render();
	void Update(float deltaTime,SDL_Event e);
	void ChangeScreen(SCREENS new_screen);
	inline void SetScore(int score) { CurrentScore = score; }
	int CurrentScore;

};

#endif //_GAMESCREENMANAGER_H