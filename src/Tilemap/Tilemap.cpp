#include "Tilemap.h"

Tilemap::Tilemap(int layers, int columns, int rows)
{
	for (int i = 0; i < layers; i++)
	{
		tilemap[i] = vector<vector<Tile>>(rows);

		for (int j = 0; j < rows; j++)
		{
			tilemap[i][j] = vector<Tile>(columns);

			for (int k = 0; k < columns; k++)
			{
				tilemap[i][j][k] = Tile();
			}
		}
	}
}

Tilemap::~Tilemap()
{

}

void Tilemap::AddTile(int layer, int column, int row, Tile& newTile)
{
	tilemap[layer][column][row] = newTile;
}