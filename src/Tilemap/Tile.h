#pragma once

#include "Tools/dll-Exp-Inp.h"
#include "Entity/Sprite.h"

using namespace sprite;

class EXPORT Tile
{
public:

	Tile(int id, bool hasCollision, std::vector<glm::vec2> UV);
	~Tile();

	glm::vec2 topRightUV;
	glm::vec2 topLeftUV;
	glm::vec2 bottomRightUV;
	glm::vec2 bottomleftUV;

	int id;
	bool hasCollision;
};

