#pragma once
#include "Tools/dll-Exp-Inp.h"
#include "Tile.h"
#include "Entity/Entity2D.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace Entity2D;

class EXPORT Tilemap : public Entity2D
{
private:

    void LoadTileMaps(const vector<const char*>& tileMapFiles);
    void LoadTileSet(const char* tileSetFile);

    TileMapLayer ReadSingleMap(const char* filename);
    vector<vector<vec2>> CalculateUVCoordsInMap(int heightTiles, int widthTiles, int totalHeight, int totalWidth, int tileHeight, int tileWidth);
    void AddToVertex(float x, float y, int tileId, vec2 UvCoord, vector<float>& vertexVector);

    vector<TileMapLayer> tileMap;
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

    float* vertex;
    int* indices;


public:

	Tilemap(const char* tileSetFile, const vector<const char*>& tileMapFiles, const char* tileMapImage, 
		    Vector4 rgba, Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);

	~Tilemap();

    void Draw();

    bool hasCollision(int layer, Entity2D entity);
    bool hasCollision(int layer, int x, int y, int width, int height);
};

