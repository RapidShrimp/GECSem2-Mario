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

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetupLevel();
}
GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete mario_character;
	mario_character = nullptr;
	delete luigi_character;
	luigi_character = nullptr;
	m_enemies.clear();
}
bool GameScreenLevel2::SetupLevel()
{
	SetLevelMap();
	mario_character = new CharacterMario(m_renderer, "Images/MarioSprite.png", Vector2D(64, 230), m_level_map);
	luigi_character = new CharacterLuigi(m_renderer, "Images/LuigiSprite.png", Vector2D(120, 230), m_level_map);
	m_background_texture = new Texture2D(m_renderer);
	CreateKoopa(Vector2D(420, 300), FACING_LEFT, KOOPA_SPEED / 4.0f);
	CreateKoopa(Vector2D(325, 32), FACING_RIGHT, KOOPA_SPEED);
	m_screenshake = false;
	m_background_yPos = 0.0f;
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

	//if (Collisions::Instance()->Circle(mario_character, luigi_character))
	//{
	//	cout << "Circle hit!" << endl;
	//}

	//if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), luigi_character->GetCollisionBox()))
	//{
	//	cout << "Box hit!" << endl;
	//}


	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);
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
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	mario_character->Render();
	luigi_character->Render();
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
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
				if (Collisions::Instance()->Circle(m_enemies[i], mario_character) || Collisions::Instance()->Circle(m_enemies[i], luigi_character))
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

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back(new CharacterKoopa(m_renderer, "Images/KoopaSpriteSheet.png", m_level_map, position, direction, speed));
}


void GameScreenLevel2::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}