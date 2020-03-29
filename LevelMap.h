#pragma once
#ifndef  _LEVELMAP_H
#define _LEVELMAP_H
#include "Constants.h"

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int h, unsigned int w, int newValue);

private:
	int** mMap;

};


#endif // ! _LEVELMAP_H



