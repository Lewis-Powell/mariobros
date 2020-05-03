#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
void LoadMusic(string path);
bool quit = false;
Mix_Music* gMusic = NULL;




int main(int argc, char* args[])
{

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

		}
		else
		{
			cout << "Renderer could not initalise. Error: " << SDL_GetError();
			return false;
		}
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not initialise. Error: " << Mix_GetError();
		return false;
	}
	else
	{
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}
	}
	return true;

}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Destroy the gmae screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release Music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

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
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	
	gameScreenManager->Render();

	//SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//SDL_RenderCopyEx(gRenderer, gTexture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	
	//Update Screen
	SDL_RenderPresent(gRenderer);
}


void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL)
	{
		cout << "Failed to load background music. Error: " << Mix_GetError() << endl;
	}
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