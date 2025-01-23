#pragma once
#include "Tools/dll-Exp-Inp.h"

#include "TilemapLayer.h"
#include "Entity/Entity2D.h"

#include <vector>

using namespace std;
using namespace Entity2D;

class EXPORT Tilemap : public Entity2D
{
private:

    void LoadTileSet(const char* tileSetFile);

    vector<vector<vec2>> CalculateUVCoordsInMap(int heightTiles, int widthTiles, int totalHeight, int totalWidth, int tileHeight, int tileWidth);

	vector<Tile> tileSet;
	unsigned int tileMapTexture;

	//Map
	int mapPixelWidth;
	int mapPixelHeight;

	int tileSetTileHeight;
	int tileSetTileWidth;

	int mapTileHeight;
	int mapTileWidth;

	int layerCount;

	//Tiles
	int tilePixelWidth;
	int tilePixelHeight;

public:

	Tilemap(const char* tileSetFile, const vector<const char*>& tileMapFiles, const char* tileMapImage, 
		    Vector4 rgba, Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);

	~Tilemap();

	vector<TilemapLayer*> layers;

    void Draw();
};

