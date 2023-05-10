#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "TextRenderer.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "CharacterKoopa.h"
#include "Coin.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* manager, bool isSingleplayer) : GameScreen(renderer) 
{ 
	m_level_map = nullptr;
	m_screen_manager = manager;
	m_singleplayer = isSingleplayer;
	SetupLevel(); 
}
GameScreenLevel1::~GameScreenLevel1() 
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
	delete m_pow_block;
	m_pow_block = nullptr;
	delete m_level_map;
	m_level_map = nullptr;
	delete m_screen_manager;
	m_screen_manager = nullptr;
	m_enemies.clear();
	m_coins.clear();
}
bool GameScreenLevel1::SetupLevel() 
{
	SetLevelMap();
	mario_character = new CharacterMario(m_renderer, "Images/MarioSprite.png", Vector2D(64, 230),m_level_map);
	if (!m_singleplayer)
	{
		luigi_character = new CharacterLuigi(m_renderer, "Images/LuigiSprite.png", Vector2D(120, 230), m_level_map);
	}
	m_background_texture = new Texture2D(m_renderer);
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	CreateKoopa(Vector2D(20, 30), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(456, 30), FACING_LEFT, KOOPA_SPEED);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	CountdownTimer = KOOPA_RESPAWN;
	m_score_text = new TextRenderer(m_renderer);
	if (m_score_text)
	{
		m_score_text->LoadFont("Fonts/PixelFont.ttf", 20, "Score: " + to_string(score), { 255, 255, 255, 255 });
	}
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) 
	{
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;
}
void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
									  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// do the screen shake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	//
	//if (Collisions::Instance()->Circle(mario_character, luigi_character))
	//{
	//	cout << "Circle hit!" << endl;
	//}

	//if (Collisions::Instance()->Box(mario_character->GetCollisionBox(),luigi_character->GetCollisionBox()))
	//{
	//	cout << "Box hit!" << endl;
	//}


	mario_character->Update(deltaTime, e);
	if (!m_singleplayer) { luigi_character->Update(deltaTime, e); }
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
	RespawnTimer(deltaTime);
	CoinTimer(deltaTime);
	if (m_score_text != nullptr && score != oldScore) 
	{
		oldScore = score;
		m_score_text->LoadFont("Fonts/PixelFont.ttf", 20, "Score: " + to_string(score), { 255,255,255,255 });
	}
}

void GameScreenLevel1::RespawnTimer(float deltaTime)
{
	CountdownTimer -= deltaTime;
	if (CountdownTimer <= 0) 
	{
		
		CreateKoopa(Vector2D(20, 30), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(456, 30), FACING_LEFT, KOOPA_SPEED);
		CountdownTimer = KOOPA_RESPAWN;
		std::cout << "Respawn" << endl;
	}
}

void GameScreenLevel1::CoinTimer(float deltaTime)
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


void GameScreenLevel1::Render()
{
	m_background_texture->Render(Vector2D(0,m_background_yPos), SDL_FLIP_NONE);
	mario_character->Render();
	if (!m_singleplayer) {luigi_character->Render();}
	m_pow_block->Render();
	for (int i = 0; i < m_enemies.size(); i++) 
	{
		m_enemies[i]->Render();
	}
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}
	m_score_text->Render(200, 10);
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
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
				{ m_enemies[i]->SetAlive(false); }
			}

			//FLIP DIRECTION
			if (m_enemies[i]->GetPosition().x > 480) {m_enemies[i]->FlipDirection(FACING_LEFT);}
			else if (m_enemies[i]->GetPosition().x < 10) { m_enemies[i]->FlipDirection(FACING_RIGHT); }



			//now do the update
			m_enemies[i]->Update(deltaTime, e);
			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i] -> GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x >SCREEN_WIDTH - 96.0f))
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
						score += 1;
					}
					else
					{
						mario_character->SetAlive(false);
						m_screen_manager->ChangeScreen(SCREEN_GAMEOVER);
						//m_screen_manager->SetScore(score);
					}
				}
				if (!m_singleplayer) 
				{
					if (Collisions::Instance()->Circle(m_enemies[i], luigi_character))
					{
						if (m_enemies[i]->GetInjured())
						{
							m_enemies[i]->SetAlive(false);
							score += 1;
						}
						else
						{
							luigi_character->SetAlive(false);
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

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
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

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction, float speed)
{
	m_coins.push_back(new Coin(m_renderer, "Images/Coin.png", m_level_map, position, direction, speed));
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back(new CharacterKoopa(m_renderer, "Images/KoopaSpriteSheet.png", m_level_map, position, direction, speed));
}


void GameScreenLevel1::UpdatePOWBlock()
{
 	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (mario_character->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario_character->CancelJump();
			}

		}
	}
	if (!m_singleplayer) 
	{
		if (Collisions::Instance()->Box(luigi_character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
		{
			if (m_pow_block->IsAvailable())
			{
				if (luigi_character->IsJumping())
				{
					DoScreenShake();
					m_pow_block->TakeHit();
					luigi_character->CancelJump();
				}

			}
		}
	}
}
void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}