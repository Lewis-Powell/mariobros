#include "GameScreenLevel2.h"
#include <iostream>

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	SetUpLevel();
}


GameScreenLevel2::~GameScreenLevel2()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}


void GameScreenLevel2::Render()
{
	//Draws Background
	mBackgroundTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
}


bool GameScreenLevel2::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/win.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
}