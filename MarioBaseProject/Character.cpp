#include "Character.h"



Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_facing_direction = FACING_RIGHT;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to Load Texture" << endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if(m_facing_direction == FACING_RIGHT){ m_texture->Render(m_position, SDL_FLIP_NONE); }
	else { m_texture->Render(m_position, SDL_FLIP_HORIZONTAL); }
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//Jumping
	if (m_jumping) 
	{
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f) 
		{
			m_jumping = false;
		}
	}
	AddGravity(deltaTime);

	//Left Right Movement
	if (m_moving_left) {MoveLeft(deltaTime);}
	else if (m_moving_right) { MoveRight(deltaTime); }

	//Update Positions
	SetPosition(GetPosition());
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVESPEED;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVESPEED;
}

void Character::Jump()
{
	if (m_can_jump) 
	{
		m_can_jump = false;
		m_jumping = true;
		m_jump_force = INITIAL_JUMP_FORCE;
	}
}

void Character::AddGravity(float deltaTime) 
{
	if ((m_position.y + 42) <= SCREEN_HEIGHT) 
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else { m_can_jump = true; }
}

