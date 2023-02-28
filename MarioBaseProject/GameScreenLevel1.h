#pragma once
#include "GameScreen.h"
#include "Commons.h"
class Texture2D;

class GameScreenLevel1 : GameScreen
{
public:
	   GameScreenLevel1(SDL_Renderer* renderer);
	   ~GameScreenLevel1();

private: 
	Texture2D* m_background_texture;
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	bool SetupLevel();
};

