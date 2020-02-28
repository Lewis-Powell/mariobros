#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
//#include "LevelMap.h"


class Texture2D;
class Character;
class LevelMap;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	void SetLevelMap();
	Character* mMarioCharacter;
	Character* mLuigiCharacter;
	LevelMap* mLevelMap;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};