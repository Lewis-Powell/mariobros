#include "Character.h"
#include "Texture2D.h"
#include <string.h>


MarioCharacter::MarioCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{

}

MarioCharacter::~MarioCharacter()
{
	mRenderer = NULL;
}

void MarioCharacter::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}


void MarioCharacter::Update(float deltaTime, SDL_Event e)
{
	if (mJumping)
	{
		//Adjust position
		mPosition.y -= mJumpForce * deltaTime;
		//Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
		//std::cout << mPosition.y << std::endl;
		//Has jump force reduced to zero?
		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}

	//Collision Position Variables
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	//Deal with gravity
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//Collided with ground so can jump again
		mCanJump = true;
		mJumping = false;
	}


	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}
	//SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingRight = false;
			mMovingLeft = true;
			break;
		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			break;
		case SDLK_SPACE:
			Jump();
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		}
	}
	if (mPosition.x < 0)
	{
		mMovingLeft = false;
	}
	else if(mPosition.x > SCREEN_WIDTH - mTexture->GetWidth())
	{
		mMovingRight = false;
	}
}