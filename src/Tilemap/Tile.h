#pragma once

#include "Tools/dll-Exp-Inp.h"

class EXPORT Tile
{
private:

	int ID;
	bool hasCollision;

public:

	Tile();
	~Tile();

	void SetID(int value);
	int GetID();

	void SetCollision(bool value);
	bool GetCollision();
};

