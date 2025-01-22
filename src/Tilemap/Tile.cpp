#include "Tile.h"

Tile::Tile(int id, bool hasCollision, std::vector<glm::vec2> UV)
{
	this->id = id;
	this->hasCollision = hasCollision;

    this->topLeftUV = UV.at(0);
    this->topRightUV = UV.at(1);
    this->bottomleftUV = UV.at(2);
    this->bottomRightUV = UV.at(3);
}

Tile::~Tile()
{

}
