#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

class GameScreenGameOver : GameScreen
{
public:
	GameScreenGameOver(SDL_Renderer* renderer);
	~GameScreenGameOver();

	void Render();

protected:

private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
};

