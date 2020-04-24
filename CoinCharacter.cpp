#include "CoinCharacter.h"

CoinCharacter::CoinCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	
	mPosition = startPosition;

	mSingleSpriteWidth = mTexture->GetWidth() / 3; //3 Sprites int 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
}

CoinCharacter::~CoinCharacter()
{

}

void CoinCharacter::TakeDamage()
{
	//score++
}

void CoinCharacter::Render()
{

	//Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//If injured move the left position to be the left position of the 2nd image on spirte sheet.
	/*if (mInjured)
	{
		left = mSingleSpriteWidth;
	}*/

	//Get the portion of the spritesheet you want to draw
								//{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where you want it drawn.
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

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
	return mCollected;
}

void CoinCharacter::SetCollected(bool collected)
{
	mCollected = collected;
}

void CoinCharacter::Update(float deltaTime, SDL_Event e)
{

}