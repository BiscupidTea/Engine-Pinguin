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

	vector<Tile> tiles;
	vector<Tile**> tilemap;

	float width;
	float height;

	float imageWidth;
	float imageHeight;

	float tileWidth;
	float tileHeight;

	float convertedPosX;
	float convertedPosY;

	string path;

	Vector4 defaultColor = Vector4{1.0f, 1.0f, 1.0f, 1.0f};
	Vector3 defaultPosition = Vector3{0.0f, 0.0f, 0.0f};
	Vector3 defaultScale = Vector3{1.0f, 1.0f, 1.0f};
	Vector3 defaultRotation = Vector3{ 1.0f, 1.0f, 1.0f };

public:

	Tilemap(const char* textureName, Vector4 rgba, Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
	~Tilemap();
	
	Tile& GetTile(int tileID);

	void SetWidth(float value);
	void SetHeight(float value);

	void SetTileInTilemap(int layer, int column, int row, int tileID);
	void AddTile(Tile& newTile);
	void CreateTilemap();

	bool ImportTilemap(const char* filePath, Renderer* rkRenderer);

	void Draw();

	void CheckCollision(Entity2D* entity);
};

