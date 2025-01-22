#include "Tile.h"

Tile::Tile(int id, bool hasCollision, UV uvArray[4])
{
	this->id = id;
	this->hasCollision = hasCollision;

	this->uvArray[0].u = uvArray[0].u;
	this->uvArray[1].u = uvArray[1].u;
	this->uvArray[2].u = uvArray[2].u;
	this->uvArray[3].u = uvArray[3].u;

	this->uvArray[0].v = uvArray[0].v;
	this->uvArray[1].v = uvArray[1].v;
	this->uvArray[2].v = uvArray[2].v;
	this->uvArray[3].v = uvArray[3].v;
}

Tile::~Tile()
{
}
