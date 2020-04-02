#include "KoopaCharacter.h"
#include "Texture2D.h"
#include <string.h>

KoopaCharacter::KoopaCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = MovementSpeed;
	mPosition = startPosition;
	
	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2; //2 Sprites int the 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
}
