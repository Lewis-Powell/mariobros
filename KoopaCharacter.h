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
	bool GetAlive();
	void SetAlive(bool alive);
	bool GetInjured() { return mInjured; }

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;
	void FlipRightWayUp();
	float mMovementSpeed;
	bool mAlive;

protected:
	void MoveLeftK(float deltaTime);
	void MoveRightK(float deltaTime);
	//void Update(float deltaTime, SDL_Event e);
};