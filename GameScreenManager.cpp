#include "GameScreen.h"
#include "GamesScreenLevel1.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel2.h"
#include "GamesScreenManager.h"
#include "GameScreenGameOver.h"
#include "GameScreenLevel1s.h"
#include <fstream>
using namespace std;

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
	
	ofstream myfile;
	ifstream infile;
	infile.open("TxtDocs/win.txt");
	string Coins;
	getline(infile, Coins);
	infile.close();
	if (Coins == "10")
	{
		ChangeScreen(SCREEN_LEVEL2);
		ofstream myfile;
		myfile.open("TxtDocs/win.txt");
		myfile << "11";
		myfile.close();
	}

	infile.open("TxtDocs/dead.txt");
	string dead;
	getline(infile, dead);
	infile.close();
	if (dead == "0")
	{
		ChangeScreen(SCREEN_GAMEOVER);
		ofstream myfile;
		myfile.open("TxtDocs/dead.txt");
		myfile << "2";
		myfile.close();
	}
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}
	GameScreen* tempGScreen;
	GameScreenLevel1* lvl1Screen;
	GameScreenIntro* introScreen;
	GameScreenLevel2* lvl2Screen;
	GameScreenGameOver* goScreen;
	GameScreenLevel1s* lvl1sScreen;
	switch (newScreen)
	{
	case SCREEN_INTRO:
		introScreen = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)introScreen;
		introScreen = NULL;
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		lvl1Screen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)lvl1Screen;
		lvl1Screen = NULL;
		break;
	case SCREEN_LEVEL2:
		lvl2Screen = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)lvl2Screen;
		lvl2Screen = NULL;
		break;
	case SCREEN_GAMEOVER:
		goScreen = new GameScreenGameOver(mRenderer);
		mCurrentScreen = (GameScreen*)goScreen;
		goScreen = NULL;
		break;
	case SCREEN_HIGHSCORES:
		break;
	case SCREEN_LEVEL1S:
		lvl1sScreen = new GameScreenLevel1s(mRenderer);
		mCurrentScreen = (GameScreen*)lvl1sScreen;
		lvl1sScreen = NULL;
		break;
	default:
		break;
	}
	
}