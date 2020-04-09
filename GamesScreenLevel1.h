#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "KoopaCharacter.h"
#include "PowBlock.h"
#include <vector>
//#include "LevelMap.h"


class Texture2D;
class Character;
class LevelMap;
class PowBlock;
class KoopaCharacter;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	void SetLevelMap();
	Character* mMarioCharacter;
	Character* mLuigiCharacter;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	void DoScreenshake();


	//Something wrong with this line?
	std::vector<KoopaCharacter*> mEnemies;

	

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

};