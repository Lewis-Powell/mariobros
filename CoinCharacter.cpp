#include "CoinCharacter.h"

CoinCharacter::CoinCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing) : Character(renderer, imagePath, startPosition, map)
{
	mCurrentFrame = 0;
	mNotCollected = true;
	mPosition = startPosition;
	
	mFacingDirection = startFacing;
	mMovementSpeed = KOOPA_SPEED;

	mInjured = false;
	

	mSingleSpriteWidth = mTexture->GetWidth() / 3; //3 Sprites int 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
}

CoinCharacter::~CoinCharacter()
{
	mRenderer = NULL;
}

void CoinCharacter::TakeDamage()
{
	mNotCollected = false;
}

void CoinCharacter::Render()
{


	//Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//If injured move the left position to be the left position of the 2nd image on spirte sheet.
	//if (mInjured)
	//{
	//	left = mSingleSpriteWidth;
	//}

	//Get the portion of the spritesheet you want to draw
								//{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { mSingleSpriteWidth*mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where you want it drawn.
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	
	
	////Then draw it facing the correct direction.
	//if (mFacingDirection == FACING_RIGHT)
	//{
	//	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	//}
	//else
	//{
	//	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	//}
}

bool CoinCharacter::GetCollected()
{
	return mNotCollected;
}

void CoinCharacter::SetCollected(bool collected)
{
	mNotCollected = collected;
}

void CoinCharacter::Update(float deltaTime, SDL_Event e)
{

	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY;

		mCurrentFrame++;

		if (mCurrentFrame > 2)
		{
			mCurrentFrame = 0;
		}
	}


	//int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() / 2 * 0.5f)) / TILE_WIDTH;
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

}