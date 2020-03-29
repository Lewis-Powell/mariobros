#include "Character.h"
#include "Texture2D.h"
#include <string.h>

//SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map
Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mCurrentLevelMap = map;
	mRenderer = renderer;
	mPosition = startPosition;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load sprite texture!";
		//return false;
	}
	//SDL_Surface* pSurface = IMG_Load(path.c_str());
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	//Change to see what is the best fit.
	mCollisionRadius = 15.0f;
}


Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
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

void Character::Update(float deltaTime, SDL_Event e)
{
	/*if (mJumping)
	//{
	//	//Adjust position
	//	mPosition.y -= mJumpForce * deltaTime;
	//	//Reduce the jump force
	//	mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
	//	std::cout << mPosition.y << std::endl;
	//	//Has jump force reduced to zero?
	//	if (mJumpForce <= 0.0f)
	//	{
	//		mJumping = false;
	//	}
	//}

	////Collision Position Variables
	//int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	//int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	////Deal with gravity
	//if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	//{
	//	AddGravity(deltaTime);
	//}
	//else
	//{
	//	//Collided with ground so can jump again
	//	mCanJump = true;
	//	mJumping = false;
	//}


	//if (mMovingLeft)
	//{
	//	MoveLeft(deltaTime);
	//}
	//else if (mMovingRight)
	//{
	//	MoveRight(deltaTime);
	//}
	//SDL_PollEvent(&e);
	//switch (e.type)
	//{
	//case SDL_KEYDOWN:
	//	switch (e.key.keysym.sym)
	//	{
	//	case SDLK_a:
	//		mMovingRight = false;
	//		mMovingLeft = true;
	//		break;
	//	case SDLK_d:
	//		mMovingLeft = false;
	//		mMovingRight = true;
	//		break;
	//	case SDLK_SPACE:
	//		//mPosition.y -= 50;
	//		Jump();
	//		break;
	//	}
	//	break;
	//case SDL_KEYUP:
	//	switch (e.key.keysym.sym)
	//	{
	//	case SDLK_a:
	//		mMovingLeft = false;
	//		break;
	//	case SDLK_d:
	//		mMovingRight = false;
	//	}
	//} */

}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x += -MovementSpeed * deltaTime;
	mFacingDirection = FACING_LEFT;

}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += MovementSpeed * deltaTime;
	mFacingDirection = FACING_RIGHT;

}

void Character::AddGravity(float deltaTime)
{
	if (mPosition.y <= SCREEN_HEIGHT-mTexture->GetHeight())
	{
		mPosition.y += GRAVITY * deltaTime;
		mCanJump = false;
	}
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}


void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}