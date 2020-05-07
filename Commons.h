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
	Vector2D(float x1, float y1)
	{
		x = x1;
		y = y1;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Rect2D(float x1, float y1, float w1, float h1)
	{
		x = x1;
		y = y1;
		width = w1;
		height = h1;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES,
	SCREEN_LEVEL1S
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};