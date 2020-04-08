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
	mEnemies.clear();
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
	UpdateEnemies(deltaTime, e);

}

void GameScreenLevel1::Render()
{
	//Draw the enemies.
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

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

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	//Update Enemies
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Check if enemy is on bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				//Is enemy off screen to left/right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					mEnemies[i]->SetAlive(false);
				}
			}
			//Now do the update
			mEnemies[i]->Update(deltaTime, e);

			//Check to see if the enemy collides with the player
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore the collisions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemies[i], mMarioCharacater))
				{
					mMarioCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
				}
			}

			//If the enemy is no longer alive the schedule it for deletion.
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove dead enemies - 1 each update.
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}


void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	//mMarioCharacter = new MarioCharacter(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	koopaCharacter = new KoopaCharacter(mRenderer, "Images/Koopa.png", position, mLevelMap, direction);
	mEnemies.push_back(koopaCharacter);
}