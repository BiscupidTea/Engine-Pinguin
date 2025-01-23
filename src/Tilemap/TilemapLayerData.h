#pragma once
#include "Tools/dll-Exp-Inp.h"
#include <vector>

class EXPORT TilemapLayerData
{

public:
    
    std::vector<int> layer;
    int y;
    int x;

    TilemapLayerData(int width, int height);
    
    void SetTile(int posX, int posY, int id);
    int GetTileId(int posX, int posY);
};

