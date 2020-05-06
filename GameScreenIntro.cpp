#include "GameScreenIntro.h"
#include "Texture2D.h"
#include <iostream>

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	//mSingleSpriteWidth = mTexture->GetWidth() / 2; //2 Sprites int the 1 row
	//mSingleSpriteHeight = mTexture->GetHeight();
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{

}

void GameScreenIntro::Render()
{
	//Draws Background
	mBackgroundTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);

}

bool GameScreenIntro::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/titler.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
}