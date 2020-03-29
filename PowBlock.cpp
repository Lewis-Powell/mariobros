#include "PowBlock.h"


PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture " << imagePath << std::endl;
		return;
	}
	
	mLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth() / 3; //Cause 3 sprites in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
	mRenderer = renderer;
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;

}

bool PowBlock::IsAvailable()
{
	return mNumberOfHitsLeft > 0;
}

Rect2D PowBlock::GetCollisionBox()
{
	//May need to switch width and height to mSingleSpriteWidth and mSingleSpriteHeight respectively
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		//Get Portion of the spritesheet you want to draw
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);
		//{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
		SDL_Rect portionOfSingleSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
		//Determine where you want it drawn
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
		//Then Draw It
		mTexture->Render(portionOfSingleSpritesheet, destRect, SDL_FLIP_NONE);

	}
}