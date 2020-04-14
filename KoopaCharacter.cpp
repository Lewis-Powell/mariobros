#include "KoopaCharacter.h"
#include "Texture2D.h"
#include <string.h>

KoopaCharacter::KoopaCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing) : Character(renderer, imagePath, startPosition, map)
{
	mAlive = true;
	mFacingDirection = startFacing;
	mMovementSpeed = KOOPA_SPEED;
	mPosition = startPosition;
	
	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2; //2 Sprites int the 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
}

KoopaCharacter::~KoopaCharacter()
{
	mRenderer = NULL;
}

void KoopaCharacter::TakeDamage()
{
	if (mInjured == true)
	{
		//Insert code for killing the koopa
		mAlive = false;
	}
	else
	{
		mInjured = true;
		mInjured = INJURED_TIME;
		Jump();
	}

}

void KoopaCharacter::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void KoopaCharacter::FlipRightWayUp()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mFacingDirection = FACING_LEFT;
	}
	else
	{
		mFacingDirection = FACING_RIGHT;
	}
	mInjured = false;
	Jump();

}

void KoopaCharacter::Render()
{
	//Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//If injured move the left position to be the left position of the 2nd image on spirte sheet.
	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}

	//Get the portion of the spritesheet you want to draw
								//{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where you want it drawn.
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Then draw it facing the correct direction.
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void KoopaCharacter::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth()/2 * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	//Deal with gravity
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
		mJumping = true;
	}
	else
	{
		//Collided with ground so can jump again
		mCanJump = true;
		mJumping = false;
	}
	if (!mInjured)
	{
		if (mJumping == true)
		{
			mMovingLeft = false;
			mMovingRight = false;
		}
		//We are not injured so move
		else if (mFacingDirection == FACING_LEFT)
		{
			mPosition.x -= KOOPA_SPEED * deltaTime;
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mPosition.x += KOOPA_SPEED * deltaTime;
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		//We should not be moving
		mMovingLeft = false;
		mMovingRight = false;
		//Count down injured time
		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0.0)
			FlipRightWayUp();
	}
	
	if (mPosition.x < 0)
	{
		mFacingDirection = FACING_RIGHT;
		mMovingLeft = false;
	}
	else if (mPosition.x > SCREEN_WIDTH - mTexture->GetWidth() / 2)
	{
		mFacingDirection = FACING_LEFT;
		mMovingRight = false;
	}
}

bool KoopaCharacter::GetAlive()
{
	return mAlive;
}

void KoopaCharacter::SetAlive(bool alive)
{
	mAlive = alive;
}