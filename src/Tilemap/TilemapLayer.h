#pragma once
#include "Tools/dll-Exp-Inp.h"
#include "Entity/Entity2D.h"

#include "Tile.h"
#include "TilemapLayerData.h"

#include <vector>

using namespace Entity2D;

class EXPORT TilemapLayer : public Entity2D
{
public:

    TilemapLayer(const char* tileMapFiles, const char* tileMapImage, vector<Tile> tileSet, Vector4 rgba,
                 Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);

    ~TilemapLayer();

    void Draw();

    bool HasCollision(int layer, Entity2D entity);
    bool HasCollision(int layer, int x, int y, int width, int height);

private:

    TilemapLayerData ReadMap(const char* filename);
    void AddToVertex(float x, float y, int tileId, vec2 UvCoord, vector<float>& vertexVector);

    TilemapLayerData tileMap;
    vector<Tile> tileSet;

    unsigned int tileMapTexture;

    //Map
    int mapTileHeight;
    int mapTileWidth;

    float* vertex;
    int* indices;
};