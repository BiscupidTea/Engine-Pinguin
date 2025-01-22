#pragma once

#include "Tools/dll-Exp-Inp.h"
#include "Entity/Sprite.h"

using namespace sprite;

class EXPORT Tile
{
public:

	Tile(int id, bool hasCollision, UV uvArray[4]);
	~Tile();

private:

	UV uvArray[4];

	int id;
	bool hasCollision;
};

