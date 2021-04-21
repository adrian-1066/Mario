#pragma once

struct Vector2D
{
	float x;
	float y;


	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	};

	Vector2D(float int_x, float int_y)
	{
		x = int_x;
		y = int_y;
	};
};

enum SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES

};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT

};

struct Rect2D
{
	float x, y, width, height;
	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;

	}
};

