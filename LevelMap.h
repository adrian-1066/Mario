#pragma once
#ifndef _LevelMap_H
#define _LevelMap_H

#include"constant.h"

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);

	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

private:
	int** m_map;
};

#endif // !_LevelMap_H