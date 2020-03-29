#pragma once
#include <SDL.h>
#include <string.h>
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>


class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();
	void Render();
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvailable();

protected:


private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;
};

