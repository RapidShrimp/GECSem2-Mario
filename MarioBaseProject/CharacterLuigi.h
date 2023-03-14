#pragma once
#include "Character.h"
#include "Commons.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e) override;

private:
	FACING m_facing_direction;
};