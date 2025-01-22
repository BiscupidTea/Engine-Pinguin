#include "Tilemap.h"
#include "Tilemap/tinyxml2.h"

Tilemap::Tilemap(const char* tileSetFile, const vector<const char*>& tileMapFiles, const char* tileMapImage,
	             Vector4 rgba, Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation) 
	           : Entity2D(rgba, render, newPosition, newScale, newRotation)
{
	LoadTileSet(tileSetFile);
	LoadTileMaps(tileMapFiles);

	vertexSize = 36 * mapTileHeight * mapTileWidth;

	vector<float> vertexVector;

	//for (int i = 0; i < tileMap.size(); i++)
	//{

		//{
		//  // positions		    // colors					// texture coords
		//  1, 1, 0,       1.0f, 1.0f, 1.0f, 1.0f,       uvX + uvWidth, uvY + uvHeight, // top right
		//  1, 0, 0,      1.0f, 1.0f, 1.0f, 1.0f,         uvX + uvWidth, uvY, // bottom right
		//  0, 0, 0,      1.0f, 1.0f, 1.0f, 1.0f,        uvX, uvY, // bottom left
		//  0, 1, 0,       1.0f, 1.0f, 1.0f, 1.0f,       uvX, uvY + uvHeight // top left 
		//};

	for (int y = 0; y < mapTileHeight; y++)
	{
		cout << endl;

		for (int x = 0; x < mapTileWidth; x++)
		{
			int tileId = tileMap.at(1).getTileId(x, y);

			AddToVertex(static_cast<float>(1 + x), static_cast<float>(1 - y), tileId, tileId >= 0 ? tileSet.at(tileMap.at(1).getTileId(x, y)).topRightUV : vec2(0, 0), vertexVector);
			AddToVertex(static_cast<float>(1 + x), static_cast<float>(0 - y), tileId, tileId >= 0 ? tileSet.at(tileMap.at(1).getTileId(x, y)).bottomRightUV : vec2(0, 0), vertexVector);
			AddToVertex(static_cast<float>(0 + x), static_cast<float>(0 - y), tileId, tileId >= 0 ? tileSet.at(tileMap.at(1).getTileId(x, y)).bottomleftUV : vec2(0, 0), vertexVector);
			AddToVertex(static_cast<float>(0 + x), static_cast<float>(1 - y), tileId, tileId >= 0 ? tileSet.at(tileMap.at(1).getTileId(x, y)).topLeftUV : vec2(0, 0), vertexVector);
		}
	}

	indexSize = 6 * mapTileHeight * mapTileWidth;
	vector<int> indicesVector;
	
	for (int i = 0; i < mapTileWidth * mapTileHeight; i++)
	{
		indicesVector.push_back(0 + (4 * i));
		indicesVector.push_back(1 + (4 * i));
		indicesVector.push_back(3 + (4 * i));
		indicesVector.push_back(1 + (4 * i));
		indicesVector.push_back(2 + (4 * i));
		indicesVector.push_back(3 + (4 * i));
	}

	// int indices[] = {
	//     0, 1, 3,
	//     1, 2, 3
	// };

	vertex = new float[vertexSize];
	std::copy(std::begin(vertexVector), std::end(vertexVector), vertex);

	indices = new int[indexSize];
	std::copy(std::begin(indicesVector), std::end(indicesVector), indices);

	render->CreateVBuffer(vertexPositions, indexs, vertexSize, indexSize, atributeVertexSize, VAO, VBO, EBO, aColorSize, aUvSize);
	render->BindTexture(tileMapImage, tileMapTexture);
}

Tilemap::~Tilemap()
{
	delete vertex;
	delete indexs;
}

void Tilemap::Draw()
{
	render->DrawTexture(VAO, indexSize, color, model, tileMapTexture);
}

bool Tilemap::hasCollision(int layer, Entity2D entity)
{
	return true;
}

bool Tilemap::hasCollision(int layer, int x, int y, int width, int height)
{
	return true;
}

void Tilemap::LoadTileMaps(const vector<const char*>& tileMapFiles)
{
}

void Tilemap::LoadTileSet(const char* tileSetFile)
{
}

TileMapLayer Tilemap::ReadSingleMap(const char* filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error to open file: " << filename << endl;
		return TileMapLayer(0, 0);
	}

	vector<vector<int>> tempLayer;
	string line;

	while (getline(file, line))
	{
		vector<int> row;
		stringstream ss(line);
		string cell;
		
		while (getline(ss, cell, ','))
		{
			row.push_back(stoi(cell));
		}
		
		tempLayer.push_back(row);
	}

	file.close();

	int width = tempLayer[0].size();
	int height = tempLayer.size();

	mapTileHeight = height;
	mapTileWidth = width;

	TileMapLayer mapData(width, height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			mapData.setTile(x, y, tempLayer[y][x]);
		}
	}

	return mapData;
}

vector<vector<vec2>> Tilemap::CalculateUVCoordsInMap(int heightTiles, int widthTiles, int totalHeight, int totalWidth, int tileHeight, int tileWidth)
{
	vector<vector<vec2>> uvCoordsList;

	for (int i = 0; i < heightTiles; ++i)
	{
		for (int j = 0; j < widthTiles; ++j)
		{
			vector<vec2> uvCoords;

			uvCoords.push_back(vec2(static_cast<float>(j * tileWidth) / totalWidth,
				static_cast<float>(i * tileHeight) / totalHeight));
			uvCoords.push_back(vec2(static_cast<float>((j + 1) * tileWidth) / totalWidth,
				static_cast<float>(i * tileHeight) / totalHeight));
			uvCoords.push_back(vec2(static_cast<float>(j * tileWidth) / totalWidth,
				static_cast<float>((i + 1) * tileHeight) / totalHeight));
			uvCoords.push_back(vec2(static_cast<float>((j + 1) * tileWidth) / totalWidth,
				static_cast<float>((i + 1) * tileHeight) / totalHeight));

			uvCoordsList.push_back(uvCoords);
		}
	}

	return uvCoordsList;
}

void Tilemap::AddToVertex(float x, float y, int tileId, vec2 UvCoord, vector<float>& vertexVector)
{
	//position
	vertexVector.push_back(x);
	vertexVector.push_back(y);
	vertexVector.push_back(0.0f);

	//color
	vertexVector.push_back(1.0f);
	vertexVector.push_back(1.0f);
	vertexVector.push_back(1.0f);

	if (tileId >= 0)
	{
		vertexVector.push_back(1.0f);

	}

	else
	{
		vertexVector.push_back(0.0f);
	}

	//UV
	vertexVector.push_back(UvCoord.x);
	vertexVector.push_back(UvCoord.y);
}
