#include "GameScreenLevel1s.h"
#include <iostream>
#include "GamesScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "LuigiCharacter.h"
#include "GamesScreenManager.h"
#include "Constants.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


GameScreenLevel1s::GameScreenLevel1s(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	mLevelMap = NULL;
	Timer = 0;
	counter = 0;
	SetUpLevel();

}

GameScreenLevel1s::~GameScreenLevel1s()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete mMarioCharacter;
	mMarioCharacter = NULL;
	delete mLevelMap;
	mLevelMap = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	mEnemies.clear();
	mCoins.clear();

}

void GameScreenLevel1s::Update(float deltaTime, SDL_Event e)
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


	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);

	if (mMarioCharacter->GetScore() >= 10)
	{
		ofstream myfile;
		myfile.open("TxtDocs/win.txt");
		myfile << "10";
		myfile.close();
		std::cout << "You Got 10 Coins\n10 Coins!!!" << std::endl;
	}
	if (CharacterAlive == 0)
	{
		ofstream myfile;
		myfile.open("TxtDocs/dead.txt");
		myfile << "0";
		myfile.close();

	}
}

void GameScreenLevel1s::Render()
{

	//Draws PowBlock
	mPowBlock->Render();


	//Draws Character
	mMarioCharacter->Render();

	//Draw the enemies.
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}



	//Draws Background
	mBackgroundTexture->Render(Vector2D(0.0f, mBackgroundYPos), SDL_FLIP_NONE);



}

bool GameScreenLevel1s::SetUpLevel()
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
	CharacterAlive = 1;

	//Set up Coins

	CreateCoins(Vector2D(200, 64), FACING_RIGHT);
	CreateCoins(Vector2D(290, 64), FACING_LEFT);

	CreateCoins(Vector2D(150, 30), FACING_RIGHT);
	CreateCoins(Vector2D(340, 30), FACING_LEFT);

	CreateCoins(Vector2D(415, 128), FACING_RIGHT);
	CreateCoins(Vector2D(75, 128), FACING_LEFT);

	CreateCoins(Vector2D(100, 196), FACING_RIGHT);
	CreateCoins(Vector2D(390, 196), FACING_LEFT);

	CreateCoins(Vector2D(200, 256), FACING_RIGHT);
	CreateCoins(Vector2D(290, 256), FACING_LEFT);


}

void GameScreenLevel1s::SetLevelMap()
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

void GameScreenLevel1s::UpdatePowBlock()
{
	if ((Collisions::Instance()->Box(mMarioCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox())) && mPowBlock->IsAvailable())
	{
		if (mMarioCharacter->IsJumping())
		{
			mPowBlock->TakeAHit();
			mMarioCharacter->CancelJump();
			DoScreenshake();

		}

	}
}

void GameScreenLevel1s::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}

}

void GameScreenLevel1s::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (Timer <= 0)
	{
		if (counter < 4)
		{
			//Set up enemies
			CreateKoopa(Vector2D(34, 20), FACING_RIGHT, KOOPA_SPEED);
			CreateKoopa(Vector2D(445, 20), FACING_LEFT, KOOPA_SPEED);
			counter++;
		}
		Timer = 10000;
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
					if (mEnemies[i]->GetInjured())
					{
						mEnemies[i]->TakeDamage();
					}
					else
					{
						mMarioCharacter->CharacterDeath();
						CharacterAlive = 0;
					}

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


void GameScreenLevel1s::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	//mMarioCharacter = new MarioCharacter(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	KoopaCharacter* koopaCharacter = new KoopaCharacter(mRenderer, "Images/Koopa.png", position, mLevelMap, direction);
	mEnemies.push_back(koopaCharacter);
}


void GameScreenLevel1s::UpdateCoins(float deltaTime, SDL_Event e)
{

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
					mCoins[i]->SetCollected(false);
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
			mMarioCharacter->IncreaseScore();
		}
	}
}

void GameScreenLevel1s::CreateCoins(Vector2D position, FACING direction)
{
	CoinCharacter* coinCharacter = new CoinCharacter(mRenderer, "Images/Coin.png", position, mLevelMap, direction);
	mCoins.push_back(coinCharacter);
}