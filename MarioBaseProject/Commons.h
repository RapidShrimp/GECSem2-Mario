#pragma once

struct Vector2D 
{
	float x;
	float y;


	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float Initial_X, float Initial_Y) 
	{
		x = Initial_X;
		y = Initial_Y;
	}
};

