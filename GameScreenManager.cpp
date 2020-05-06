#include "GameScreen.h"
#include "GamesScreenLevel1.h"
#include "GameScreenIntro.h"
#include "GamesScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	//Ensure The First Screen is set up
	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;

}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}
	GameScreen* tempGScreen;
	GameScreenLevel1* tempScreen;
	GameScreenIntro* temprScreen;
	switch (newScreen)
	{
	case SCREEN_INTRO:
		temprScreen = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)temprScreen;
		tempScreen = NULL;
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
	
}