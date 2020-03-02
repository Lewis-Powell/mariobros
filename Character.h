#pragma once
#include <SDL.h>
#include <iostream>
#include <string.h>
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	LevelMap* mCurrentLevelMap;

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();
	float mCollisionRadius;
	bool mCanJump;
	bool mJumping;
	float mJumpForce;
};

