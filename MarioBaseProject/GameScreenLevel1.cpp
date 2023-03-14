#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) 
{ 
	SetupLevel(); 
}

GameScreenLevel1::~GameScreenLevel1() 
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete mario_character;
	mario_character = nullptr;
}


bool GameScreenLevel1::SetupLevel() 
{
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 230));
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp")) 
	{
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mario_character->Update(deltaTime, e);
}

void GameScreenLevel1::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	mario_character->Render();
}