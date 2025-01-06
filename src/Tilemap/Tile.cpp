#include "Tile.h"

Tile::Tile()
{
	ID = 0;
	hasCollision = false;
}

Tile::~Tile()
{
}

void Tile::SetID(int value)
{
	ID = value;
}

int Tile::GetID()
{
	return ID;
}

void Tile::SetCollision(bool value)
{
	hasCollision = value;
}

bool Tile::GetCollision()
{
	return hasCollision;
}