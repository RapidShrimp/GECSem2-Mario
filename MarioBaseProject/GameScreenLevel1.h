#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include <vector>
class Texture2D;
class Character;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class LevelMap;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	   GameScreenLevel1(SDL_Renderer* renderer);
	   ~GameScreenLevel1();

	   void Render() override;
	   void Update(float deltaTime, SDL_Event e) override;

	   void UpdatePOWBlock();
private: 
	Texture2D* m_background_texture;
	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	vector<CharacterKoopa*> m_enemies;
	bool SetupLevel();
	void SetLevelMap();
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

};

