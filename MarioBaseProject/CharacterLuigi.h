#pragma once
#include "Character.h"
#include "Commons.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	int m_single_sprite_w;
	int m_single_sprite_h;
	int m_current_frame;
	int m_frame_delay;

	int GetWidth() override { return m_single_sprite_w; }
	int GetHeight() override { return m_single_sprite_h; }
private:
	FACING m_facing_direction;
};