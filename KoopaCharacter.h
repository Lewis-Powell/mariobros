#pragma once
#include "Character.h"



class KoopaCharacter : public Character
{
public:
	KoopaCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing);
	~KoopaCharacter();

	void TakeDamage();
	void Jump();
	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;
	void FlipRightWayUp();
	float mMovementSpeed;

protected:
	//void Update(float deltaTime, SDL_Event e);
};