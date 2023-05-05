#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include <vector>
#include "Coin.h"
#include "GameScreenManager.h"
class Texture2D;
class Character;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class LevelMap;
class GameScreenManager;
class Coin;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer, GameScreenManager* manager, bool IsSingleplayer);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void CoinTimer(float deltaTime);
	void RespawnTimer(float deltaTime);
private:
	Texture2D* m_background_texture;
	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;
	LevelMap* m_level_map;
	vector<CharacterKoopa*> m_enemies;
	vector<Coin*>m_coins;
	GameScreenManager* m_screen_manager;
	bool m_singleplayer;
	bool SetupLevel();
	void SetLevelMap();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoin(Vector2D position, FACING direction, float speed);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	float CountdownTimer;
	int score;
};

