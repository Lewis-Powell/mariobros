#pragma once
#include "Character.h"


class CoinCharacter : public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mCollected;


protected:

public:
	CoinCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CoinCharacter();

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void TakeDamage();

	bool GetCollected();
	void SetCollected(bool collected);

};

