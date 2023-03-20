#pragma once
#include "GameScreen.h"
#include "Commons.h"
class Texture2D;
class Character;
class CharacterMario;
class CharacterLuigi;
class LevelMap;

class GameScreenLevel1 : GameScreen
{
public:
	   GameScreenLevel1(SDL_Renderer* renderer);
	   ~GameScreenLevel1();

	   void Render() override;
	   void Update(float deltaTime, SDL_Event e) override;
private: 
	Texture2D* m_background_texture;
	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;
	LevelMap* m_level_map;
	bool SetupLevel();
	void SetLevelMap();
};

