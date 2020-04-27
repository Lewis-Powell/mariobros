#include <iostream>
#include "GamesScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "LuigiCharacter.h"

float Timer2 = 10;


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	mLevelMap = NULL;
	Timer = 0;
	//float Timer2 = 10;
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
	mCoins.clear();
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
	UpdateCoins(deltaTime, e);
}

void GameScreenLevel1::Render()
{


	//Draws Background
	mBackgroundTexture->Render(Vector2D(0.0f,mBackgroundYPos), SDL_FLIP_NONE);
	
	//Draw the enemies.
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}

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


	//Set up enemies
	//CreateKoopa(Vector2D(100, 32), FACING_RIGHT, KOOPA_SPEED);
	//CreateKoopa(Vector2D(375, 32), FACING_LEFT, KOOPA_SPEED);

	CreateCoins(Vector2D(200, 64), FACING_RIGHT);
	CreateCoins(Vector2D(275, 64), FACING_LEFT);

	
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
	for (int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}

}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (Timer <= 0)
	{
		//Set up enemies
		CreateKoopa(Vector2D(100, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(375, 32), FACING_LEFT, KOOPA_SPEED);
		Timer = 30000;
	}
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
					std::cout << "1";
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
				if (Collisions::Instance()->Circle(mEnemies[i], mMarioCharacter))
				{
					//mMarioCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
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
	Timer--;
}


void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	//mMarioCharacter = new MarioCharacter(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	KoopaCharacter* koopaCharacter = new KoopaCharacter(mRenderer, "Images/Koopa.png", position, mLevelMap, direction);
	mEnemies.push_back(koopaCharacter);
}


void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (Timer2 <= 0)
	{
		//Set up coins
		CreateCoins(Vector2D(100, 32), FACING_RIGHT);
		CreateCoins(Vector2D(375, 32), FACING_LEFT);
		Timer2 = 30000;
	}

	//Update Enemies
	if (!mCoins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			//Check if enemy is on bottom row of tiles
			if (mCoins[i]->GetPosition().y > 300.0f)
			{
				//Is enemy off screen to left/right?
				if (mCoins[i]->GetPosition().x < (float)(-mCoins[i]->GetCollisionBox().width * 0.5f) || mCoins[i]->GetPosition().x > SCREEN_WIDTH - (float)(mCoins[i]->GetCollisionBox().width * 0.55f))
				{
					mCoins[i]->SetCollected(false);
					std::cout << "1";
				}
			}
			//Now do the update
			mCoins[i]->Update(deltaTime, e);

			//Check to see if the enemy collides with the player
			if ((mCoins[i]->GetPosition().y > 300.0f || mCoins[i]->GetPosition().y <= 64.0f) && (mCoins[i]->GetPosition().x < 64.0f || mCoins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore the collisions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mCoins[i], mMarioCharacter))
				{
					//mMarioCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
				}
			}

			//If the enemy is no longer alive the schedule it for deletion.
			if (!mCoins[i]->GetCollected())
			{
				coinIndexToDelete = i;
			}
		}

		//Remove dead enemies - 1 each update.
		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
	Timer2--;
}

void GameScreenLevel1::CreateCoins(Vector2D position, FACING direction)
{
	CoinCharacter* coinCharacter = new CoinCharacter(mRenderer, "Images/Coin.png", position, mLevelMap, direction);
	mCoins.push_back(coinCharacter);
}