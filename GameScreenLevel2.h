#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();

protected:

private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
};

