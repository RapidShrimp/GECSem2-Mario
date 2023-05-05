#include "GameScreenLevel2.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "CharacterKoopa.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <iostream>

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, GameScreenManager* manager, bool IsSingleplayer) : GameScreen(renderer)
{
	m_screen_manager = manager;
	m_singleplayer = IsSingleplayer;
	m_level_map = nullptr;
	SetupLevel();
}
GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete mario_character;
	mario_character = nullptr;
	if (!m_singleplayer) 
	{
		delete luigi_character;
		luigi_character = nullptr;
	}
	delete m_screen_manager;
	m_screen_manager = nullptr;
	m_enemies.clear();
	m_coins.clear();
}
bool GameScreenLevel2::SetupLevel()
{
	SetLevelMap();
	mario_character = new CharacterMario(m_renderer, "Images/MarioSprite.png", Vector2D(64, 230), m_level_map);
	if (!m_singleplayer) { luigi_character = new CharacterLuigi(m_renderer, "Images/LuigiSprite.png", Vector2D(120, 230), m_level_map); }
	m_background_texture = new Texture2D(m_renderer);
	CreateKoopa(Vector2D(325, 32), FACING_RIGHT, KOOPA_SPEED);

	CountdownTimer = KOOPA_RESPAWN;

	if (!m_background_texture->LoadFromFile("Images/BackgroundMBL2.png"))
	{
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;
}
void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
									  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}
void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	mario_character->Update(deltaTime, e);
	if (!m_singleplayer) { luigi_character->Update(deltaTime, e); }
	UpdateEnemies(deltaTime, e);
	RespawnTimer(deltaTime);
}

void GameScreenLevel2::RespawnTimer(float deltaTime)
{
	CountdownTimer -= deltaTime;
	if (CountdownTimer <= 0)
	{

		CreateKoopa(Vector2D(420, 300), FACING_LEFT, KOOPA_SPEED / 4.0f);
		CreateKoopa(Vector2D(325, 32), FACING_RIGHT, KOOPA_SPEED);
		CountdownTimer = KOOPA_RESPAWN;
		std::cout << "Respawn" << endl;
	}
}


void GameScreenLevel2::Render()
{
	m_background_texture->Render(Vector2D(0,0), SDL_FLIP_NONE);
	mario_character->Render();
	if (!m_singleplayer) { luigi_character->Render(); }
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}
}


void GameScreenLevel2::CreateCoin(Vector2D position, FACING direction, float speed)
{
	m_coins.push_back(new Coin(m_renderer, "Images/Coin.png", m_level_map, position, direction, speed));
}

void GameScreenLevel2::CoinTimer(float deltaTime)
{
	CountdownTimer -= deltaTime;
	if (CountdownTimer <= 0)
	{

		CreateCoin(Vector2D(20, 30), FACING_RIGHT, COIN_SPEED);
		CreateCoin(Vector2D(456, 30), FACING_LEFT, COIN_SPEED);
		CountdownTimer = COIN_SPAWN;
		std::cout << "Respawn" << endl;
	}
}
void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					m_enemies[i]->SetAlive(false);
				}
			}

			//FLIP DIRECTION
			if (m_enemies[i]->GetPosition().x > 480) { m_enemies[i]->FlipDirection(FACING_LEFT); }
			else if (m_enemies[i]->GetPosition().x < 10) { m_enemies[i]->FlipDirection(FACING_RIGHT); }



			//now do the update
			m_enemies[i]->Update(deltaTime, e);
			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x >SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario_character))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
					}
				}
				if (!m_singleplayer)
				{
					if (Collisions::Instance()->Circle(m_enemies[i], luigi_character))
					{
						if (m_enemies[i]->GetInjured())
						{
							m_enemies[i]->SetAlive(false);
						}
						else
						{
							//kill luigi
						}
					}
				}
			}
			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}
void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			//check if the coin is on the bottom row of tiles
			if (m_coins[i]->GetPosition().y > 300.0f)
			{
				//is the coin off screen to the left / right?
				if (m_coins[i]->GetPosition().x < (float)(m_coins[i]->GetCollisionBox().width * 0.5f) || m_coins[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_coins[i]->GetCollisionBox().width * 0.55f))
				{
					m_coins[i]->SetAlive(false);
				}
			}

			//FLIP DIRECTION
			if (m_coins[i]->GetPosition().x > 480) { m_coins[i]->FlipDirection(FACING_LEFT); }
			else if (m_coins[i]->GetPosition().x < 10) { m_coins[i]->FlipDirection(FACING_RIGHT); }

			//now do the update
			m_coins[i]->Update(deltaTime, e);
			//check to see if coin collides with player
			if (!m_singleplayer)
			{
				if (Collisions::Instance()->Circle(m_coins[i], luigi_character))
				{
					m_coins[i]->CollectCoin();
					score += 1;
				}
			}

			if (Collisions::Instance()->Circle(m_coins[i], mario_character))
			{
				m_coins[i]->CollectCoin();
				score += 1;
			}
			//if the enemy is no longer alive then schedule it for deletion
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}
		//remove dead enemies -1 each update
		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back(new CharacterKoopa(m_renderer, "Images/KoopaSpriteSheet.png", m_level_map, position, direction, speed));
}

