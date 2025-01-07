#pragma once
#include "Tools/dll-Exp-Inp.h"
#include "Tile.h"
#include "Entity/Sprite.h"

#include <iostream>
#include <vector>

using namespace std;

class EXPORT Tilemap
{
private:

	vector<vector<vector<Tile>>> tilemap;

	int layers, columns, rows;

public:

	Tilemap(int layers, int columns, int rows);
	~Tilemap();
	
	void AddTile(int layer, int column, int row, Tile& newTile);
};

