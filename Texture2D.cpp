#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
//#include "Commons.h"
using namespace::std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	 mRenderer = renderer;
	SDL_Texture* mTexture = NULL;

	int mWidth;
	int mHeight;
}

Texture2D::~Texture2D()
{
	//Free up memory
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	Free();
	//SDL_Texture* mTexture = NULL;
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0xFF, 0xFF, 0xFF));
		mWidth = pSurface->w;
		mHeight = pSurface->h;
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		

	}
	else
		{
			cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
		}
	SDL_FreeSurface(pSurface);
	return mTexture != NULL;
}

void Texture2D::Free()
{

	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


//All rendering goes through this so if render problem probably here
void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(mRenderer);
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
	//SDL_RenderPresent(mRenderer);

}