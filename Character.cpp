#include "Character.h"
#include "Texture2D.h"
#include <string.h>

//SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map
Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mCurrentLevelMap = map;
	mRenderer = renderer;
	mPosition = startPosition;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load sprite texture!";
		//return false;
	}
	//SDL_Surface* pSurface = IMG_Load(path.c_str());
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	//Change to see what is the best fit.
	mCollisionRadius = 15.0f;
}


Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	if (mPosition.x < (float)(GetCollisionBox().width * 0.5f) && (mPosition.y < 64 || mPosition.y > 300))
	{
		mPosition.x = SCREEN_WIDTH-33;
		mPosition.y = 15;
	}
	else if (mPosition.x > SCREEN_WIDTH - 32 && (mPosition.y < 64 || mPosition.y > 300))
	{
		mPosition.x = 30;
		mPosition.y = 15;
	//mPosition.x > SCREEN_WIDTH - mTexture->GetWidth()
	}
}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x += -MovementSpeed * deltaTime;
	mFacingDirection = FACING_LEFT;

}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += MovementSpeed * deltaTime;
	mFacingDirection = FACING_RIGHT;

}

void Character::AddGravity(float deltaTime)
{
	if (mPosition.y <= SCREEN_HEIGHT-mTexture->GetHeight())
	{
		mPosition.y += GRAVITY * deltaTime;
		mCanJump = false;
	}
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}


void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

bool Character::IsJumping()
{
	return mJumping;
}

void Character::CancelJump()
{
	mJumpForce = 0.0f;
	mJumping = false;

}

void Character::IncreaseScore()
{

}

int Character::GetScore()
{
	return 0;
}