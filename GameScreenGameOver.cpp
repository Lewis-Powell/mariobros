#include "GameScreenGameOver.h"
#include <iostream>

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	SetUpLevel();
}


GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}


void GameScreenGameOver::Render()
{
	//Draws Background
	mBackgroundTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
}


bool GameScreenGameOver::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/gameover.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
}