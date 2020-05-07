#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "Constants.h"
#include "KoopaCharacter.h"
#include "CoinCharacter.h"
#include "PowBlock.h"
#include <vector>


class Texture2D;
class Character;
class LevelMap;
class PowBlock;
class KoopaCharacter;
class CoinCharacter;

class GameScreenLevel1s : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	void SetLevelMap();
	Character* mMarioCharacter;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	float Timer;
	int CharacterAlive;

	void DoScreenshake();

	int counter;

	std::vector<KoopaCharacter*> mEnemies;

	std::vector<CoinCharacter*> mCoins;



public:
	GameScreenLevel1s(SDL_Renderer* renderer);
	~GameScreenLevel1s();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoins(Vector2D position, FACING direction);
};

