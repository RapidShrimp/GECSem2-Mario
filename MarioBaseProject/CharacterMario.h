#pragma once
#include "Character.h"
#include "Commons.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }
	void Update(float deltaTime, SDL_Event e) override;

private:
	FACING m_facing_direction;
};

