#include "CharacterLuigi.h"
CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = FACING_RIGHT;
	m_collision_radius = 15.0f;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	m_audio = new AudioComponent();
	m_audio->LoadAudioFromFile("Music/Jump.mp3", 0, 1);
	//m_death_audio->LoadAudioFromFile("Music/Death.mp3", 0, 2);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to Load Texture" << endl;
	}
	m_single_sprite_w = m_texture->GetWidth() / 7;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterLuigi::~CharacterLuigi()
{
	delete m_renderer;
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
	delete m_audio;
	m_audio = nullptr;
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
			m_facing_direction = FACING_RIGHT;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			m_moving_left = false;
			m_facing_direction = FACING_LEFT;
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
	m_frame_delay -= deltaTime;

	if (IsJumping())
	{
		m_current_frame = 5;
	}
	else if (m_moving_left || m_moving_right)
	{
		if (m_frame_delay <= 0.0f)
		{
			m_frame_delay = 100;
			m_current_frame++;
			if (m_current_frame > 3)
			{
				m_current_frame = 0;
			}
		}
	}

	else m_current_frame = 0;
}

void CharacterLuigi::Render()
{
	//get the portion of the sprite sheet you want to draw
//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w,m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y) - m_single_sprite_h + 14, 32, 42 };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}
