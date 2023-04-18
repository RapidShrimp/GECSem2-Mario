#include "CharacterLuigi.h"
CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = FACING_RIGHT;
	m_collision_radius = 15.0f;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	m_audio = new AudioComponent(m_renderer);
	m_audio->LoadAudioFromFile("Music/Jump.mp3", 0, 1);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to Load Texture" << endl;
	}
}

CharacterLuigi::~CharacterLuigi()
{
}



void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			m_moving_right = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			m_moving_left = false;
			break;
		case SDLK_UP:
			if (m_can_jump)
			{
				Jump();
			}
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
		break;
	}
	Character::Update(deltaTime, e);
}