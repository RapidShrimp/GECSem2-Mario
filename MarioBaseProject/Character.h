#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>
#include "AudioComponent.h"


class Texture2D;
class AudioComponent;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	AudioComponent* m_audio;

	bool m_moving_left;
	bool m_moving_right;
	float m_collision_radius;

	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	bool m_alive;
	

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();
	virtual bool IsJumping() { return m_jumping; }
	virtual void CancelJump() { m_jumping = false; }

private:
	FACING m_facing_direction;
	LevelMap* m_current_level_map;
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~Character();
	Rect2D GetCollisionBox() 
	{
		return Rect2D(m_position.x, m_position.y,
			m_texture->GetWidth(), m_texture->GetHeight());
	}


	float GetCollisionRadius();
	void SetAlive(bool isAlive);
	bool GetAlive() { return m_alive; }
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
};

#endif _CHARACTER_H