#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

class GameScreenIntro : GameScreen
{

public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render();

private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
protected:


};

