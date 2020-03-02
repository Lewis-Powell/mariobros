#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "GamesScreenManager.h"
using namespace std;

GameScreenManager* gameScreenManager;
Uint32 gOldTime;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//Texture2D* gTexture = NULL;



bool InitSDL();
void CloseSDL();
bool Update();
void Render();
//SDL_Texture* LoadTextureFromFile(string path);
//void FreeTexture();


int main(int argc, char* args[])
{

	bool quit = false;
	if (InitSDL())
	{
		//Set up the game screen manager - starts with lvl1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		gOldTime = SDL_GetTicks();
		//GameLoop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();


	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
	}
	else
	{
		//Creates window
		gWindow = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//Initalise Picture loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initalise. Error: " << IMG_GetError();
				return false;
			}
			//gTexture = new Texture2D(gRenderer);
			//if (!gTexture->LoadFromFile("Images/test.bmp"))
			//{
				//return false;
			//}
				//LoadTextureFromFile("Images/test.bmp");
			/*if (gTexture == NULL)
			{
				return false;
			}*/

		}
		else
		{
			cout << "Renderer could not initalise. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;

}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//FreeTexture();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	//delete gTexture;
	//gTexture = NULL;

	//Destroy the gmae screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	//Get the new time
	Uint32 newTime = SDL_GetTicks();

	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return true;
		}
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;

	return false;
}

void Render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	gameScreenManager->Render();

	//SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//SDL_RenderCopyEx(gRenderer, gTexture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	
	//Update Screen
	SDL_RenderPresent(gRenderer);
}

//SDL_Texture* LoadTextureFromFile(string path)//C:\Users\LJP67\source\repos\mario\mario\Images\test.bmp)
//{
//	//FreeTexture();
//	SDL_Texture* pTexture = NULL;
//	SDL_Surface* pSurface = IMG_Load(path.c_str());
//	if (pSurface != NULL)
//	{
//		pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
//		if (pTexture != NULL)
//		{
//			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
//		}
//		else
//		{
//			cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
//		}
//	}
//	SDL_FreeSurface(pSurface);
//	return pTexture;
//}

//void FreeTexture()
//{
//	if (gTexture != NULL)
//	{
//		SDL_DestroyTexture(gTexture);
//		gTexture = NULL;
//	}
//}