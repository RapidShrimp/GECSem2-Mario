#pragma once
#include "Character.h"
class CharacterKoopa : public Character
{
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_injured_time;
	bool m_injured;
	void FlipRightwayUp();
	FACING m_facing_direction;
	float m_movement_speed;
public:
	void TakeDamage();
	void Jump();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void SetAlive(bool isAlive);
	bool GetAlive() { return m_alive; }
	bool GetInjured() { return m_injured; }
};

