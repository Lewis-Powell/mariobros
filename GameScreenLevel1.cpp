#include <iostream>
#include "GamesScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "LuigiCharacter.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	mLevelMap = NULL;
	SetUpLevel();

}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete mMarioCharacter;
	mMarioCharacter = NULL;
	delete mLuigiCharacter;
	mLuigiCharacter = NULL;
	delete mLevelMap;
	mLevelMap = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Do Screenshake if required
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the shake after the duration
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	//Update the player
	mMarioCharacter->Update(deltaTime, e);
	mLuigiCharacter->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(mMarioCharacter, mLuigiCharacter))
	{
		std::cout << "Collided Circle";
	}
	if (Collisions::Instance()->Box(mMarioCharacter->GetCollisionBox(), mLuigiCharacter->GetCollisionBox()))
	{
		std::cout << "Collided Box";
	}

	UpdatePowBlock();

}

void GameScreenLevel1::Render()
{
	//Draws Background
	mBackgroundTexture->Render(Vector2D(0.0f,mBackgroundYPos), SDL_FLIP_NONE);
	
	//Draws PowBlock
	mPowBlock->Render();

	//Draws Character
	mMarioCharacter->Render();
	mLuigiCharacter->Render();

}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
	SetLevelMap();

	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	//Set up the player character
	mMarioCharacter = new MarioCharacter(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	mLuigiCharacter = new LuigiCharacter(mRenderer, "Images/Luigi.png", Vector2D(100, 330), mLevelMap);
}
 
void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}
	//Set up new map
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePowBlock()
{
	if ((Collisions::Instance()->Box(mMarioCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox())) && mPowBlock->IsAvailable())
	{
		if (mMarioCharacter->IsJumping())
		{
			DoScreenshake();
			mPowBlock->TakeAHit();
			mMarioCharacter->CancelJump();
		}
		
	}
	if ((Collisions::Instance()->Box(mLuigiCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox())) && mPowBlock->IsAvailable())
	{
		if (mLuigiCharacter->IsJumping())
		{
			DoScreenshake();
			mPowBlock->TakeAHit();
			mLuigiCharacter->CancelJump();
		}

	}
}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

}