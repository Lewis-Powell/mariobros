#pragma once
#include "Character.h"


class LuigiCharacter : public Character
{
public:
	LuigiCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~LuigiCharacter();
	
	void Update(float deltaTime, SDL_Event e);
	void Render();
private:

protected:

};