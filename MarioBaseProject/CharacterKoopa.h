#pragma once
#include "Character.h"
class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	void SetAlive(bool isAlive);
	bool GetAlive() { return m_alive; }
	bool GetInjured() { return m_injured; }
	void FlipDirection(FACING direction);

	int m_single_sprite_w;
	int m_single_sprite_h;
	int m_current_frame;
	int m_frame_delay;
	int GetWidth() override { return m_single_sprite_w; }
	int GetHeight() override { return m_single_sprite_h; }

private:
	float m_injured_time;
	bool m_injured;
	void FlipRightwayUp();
	FACING m_facing_direction;
	float m_movement_speed;

};

