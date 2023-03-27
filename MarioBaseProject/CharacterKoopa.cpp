#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;
	m_single_sprite_w = m_texture->GetWidth()/2;
	m_single_sprite_h = m_texture->GetHeight();
}

void CharacterKoopa::FlipRightwayUp()
{
	if (m_facing_direction == FACING_LEFT) 
	{
		m_facing_direction = FACING_RIGHT;
	}
	else { m_facing_direction = FACING_LEFT; }
	m_injured = false;
	Jump();
}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!m_jumping) 
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}


void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	if (!m_injured)
	{
		//enemy is not injured so move
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		//we should not be moving when injured
		m_moving_right = false;
		m_moving_left = false;

		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0) 
		{ FlipRightwayUp(); }
			
	}
}

void CharacterKoopa::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}
