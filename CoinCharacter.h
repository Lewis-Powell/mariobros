#pragma once
#include "Character.h"


class CoinCharacter : public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mNotCollected;


	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;
	float Timer;

	float mFrameDelay;
	int mCurrentFrame;

protected:

public:
	CoinCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing);
	~CoinCharacter();

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void TakeDamage();

	//void TakeDamage();

	bool GetCollected();
	void SetCollected(bool collected);

};

