#pragma once
#include "Character.h"
class Coin : public Character
{
public:
	Coin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~Coin();
	void Jump();
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	void SetAlive(bool isAlive);
	void CollectCoin();
	bool GetAlive() { return m_alive; }
	void FlipDirection(FACING direction);
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_movement_speed;
	float m_frame_delay;
	float m_current_frame;
	void FlipRightwayUp();
	FACING m_facing_direction;
};


