#include "TilemapLayerData.h"

#include <iostream>

TilemapLayerData::TilemapLayerData(int width, int height)
{
	x = width;
	y = height;
	layer.resize(x * y, 0);
}

void TilemapLayerData::SetTile(int posX, int posY, int id)
{
	layer[(posY * x) + posX] = id;
}

int TilemapLayerData::GetTileId(int posX, int posY)
{
	return layer[(posY * x) + posX];
}
