#include "TilemapLayer.h"

TilemapLayer::TilemapLayer(const char* tileMapFiles, const char* tileMapImage, vector<Tile> tileSet, Vector4 rgba,
	Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation) :
	Entity2D(rgba, renderer, newPosition, newScale, newRotation), tileMap(0, 0)
{
	this->tileSet = tileSet;
	tileMap = ReadMap(tileMapFiles);

	const int quadDataLenght = 36; //(position*3 + colors*4 + texture coords*2) * 4
	const int quadindexDataLenght = 6; // indices = 0, 1, 3, 1, 2, 3
	const int vertexPerQuad = 4;

	vertexSize = quadDataLenght * mapTileHeight * mapTileWidth;
	vector<float> vertexVector;

	for (int y = 0; y < mapTileHeight; y++)
	{
		for (int x = 0; x < mapTileWidth; x++)
		{
			int tileId = tileMap.GetTileId(x, y);

			AddToVertex(static_cast<float>(1 + x), static_cast<float>(1 - y), tileId,
				tileId >= 0 ? tileSet.at(tileMap.GetTileId(x, y)).topRightUV : vec2(0, 0), vertexVector);

			AddToVertex(static_cast<float>(1 + x), static_cast<float>(0 - y), tileId,
				tileId >= 0 ? tileSet.at(tileMap.GetTileId(x, y)).bottomRightUV : vec2(0, 0), vertexVector);

			AddToVertex(static_cast<float>(0 + x), static_cast<float>(0 - y), tileId,
				tileId >= 0 ? tileSet.at(tileMap.GetTileId(x, y)).bottomleftUV : vec2(0, 0), vertexVector);

			AddToVertex(static_cast<float>(0 + x), static_cast<float>(1 - y), tileId,
				tileId >= 0 ? tileSet.at(tileMap.GetTileId(x, y)).topLeftUV : vec2(0, 0), vertexVector);
		}
	}

	indexSize = quadindexDataLenght * mapTileHeight * mapTileWidth;
	vector<int> indicesVector;

	for (int i = 0; i < mapTileWidth * mapTileHeight; i++)
	{
		indicesVector.push_back(0 + (vertexPerQuad * i));
		indicesVector.push_back(1 + (vertexPerQuad * i));
		indicesVector.push_back(3 + (vertexPerQuad * i));
		indicesVector.push_back(1 + (vertexPerQuad * i));
		indicesVector.push_back(2 + (vertexPerQuad * i));
		indicesVector.push_back(3 + (vertexPerQuad * i));
	}

	vertex = new float[vertexSize];
	std::copy(std::begin(vertexVector), std::end(vertexVector), vertex);

	indices = new int[indexSize];
	std::copy(std::begin(indicesVector), std::end(indicesVector), indices);

	renderer->CreateVBuffer(vertex, indices, vertexSize, indexSize, atributeVertexSize, VAO, VBO, EBO, aColorSize, aUvSize);
	renderer->BindTexture(tileMapImage, tileMapTexture);
}

TilemapLayer::~TilemapLayer()
{
	delete[] vertex;
	delete[] indices;
}

void TilemapLayer::Draw()
{
	DrawTexture(tileMapTexture);
}

bool TilemapLayer::HasCollision(Entity2D entity)
{
	int collisionMargin = 2;

	float objectPositionX = entity.getPosition().x;
	float objectPositionY = entity.getPosition().y;
	float objectScaleX = entity.getScale().x;
	float objectScaleY = entity.getScale().y;

	int minTileX = std::max(0, (int)((objectPositionX - getPosition().x) / getScale().x) - collisionMargin);
	
	int maxTileX = std::min(mapTileWidth - 1, (int)((objectPositionX + objectScaleX - getPosition().x) / getScale().x) + collisionMargin);
	
	int minTileY = std::max(0, (int)((getPosition().y - (objectPositionY + objectScaleY)) / getScale().y) - collisionMargin);
	
	int maxTileY = std::min(mapTileHeight - 1, (int)((getPosition().y - objectPositionY) / getScale().y) + collisionMargin);

	for (int y = minTileY; y <= maxTileY; y++)
	{
		for (int x = minTileX; x <= maxTileX; x++)
		{
			int tile_id = tileMap.GetTileId(x, y);

			if (tile_id != -1 && tileSet[tile_id].hasCollision)
			{
				float tilePosX = getPosition().x + x * getScale().x;
				float tilePosY = getPosition().y - y * getScale().y;

				if (CollisionManager::CheckCollisionTileEntity(
					entity, tilePosX, tilePosY, getScale().x, getScale().y))
				{
					return true;
				}
			}
		}
	}

	return false;
}

TilemapLayerData TilemapLayer::ReadMap(const char* filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error to open file: " << filename << endl;
		return TilemapLayerData(0, 0);
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

	TilemapLayerData mapData(width, height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			mapData.SetTile(x, y, tempLayer[y][x]);
		}
	}

	return mapData;
}

void TilemapLayer::AddToVertex(float x, float y, int tileId, vec2 UvCoord, vector<float>& vertexVector)
{
	//position
	vertexVector.push_back(x);
	vertexVector.push_back(y);
	vertexVector.push_back(0.0f);

	//color
	vertexVector.push_back(1.0f);
	vertexVector.push_back(1.0f);
	vertexVector.push_back(1.0f);
	vertexVector.push_back(tileId >= 0 ? 1.0f : 0.0f);

	//UV
	vertexVector.push_back(UvCoord.x);
	vertexVector.push_back(UvCoord.y);
}
