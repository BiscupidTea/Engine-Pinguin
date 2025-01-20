#include "Tilemap.h"
#include "Tilemap/tinyxml2.h"

Tilemap::Tilemap(const char* textureName, Vector4 rgba, Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation) : Entity2D(rgba, render, newPosition, newScale, newRotation)
{
	ImportTilemap(textureName, renderer);
}

Tilemap::~Tilemap()
{

}

const Tile& Tilemap::GetTile(unsigned int tileID)
{
	Tile* invalidTile = nullptr;

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tileID == tiles[i].GetID())
		{
			return tiles[i];
		}
	}

	return *invalidTile;
}

void Tilemap::SetWidth(float value)
{
	width = value;
}

void Tilemap::SetHeight(float value)
{
	height = value;
}

void Tilemap::SetTileInTilemap(int layer, int column, int row, int tileID)
{
	tilemap[layer][column][row] = GetTile(tileID);
}

void Tilemap::AddTile(Tile& newTile)
{
	tiles.push_back(newTile);
}

void Tilemap::CreateTilemap()
{
	Tile** auxTilemap;

	auxTilemap = new Tile*[height];

	for (int i = 0; i < height; i++)
	{
		auxTilemap[i] = new Tile[width];
	}

	tilemap.push_back(auxTilemap);
}

bool Tilemap::ImportTilemap(const char* filePath, Renderer* renderer)
{
	//***********************************************************************************************************************
	//Load TMX file.
	tinyxml2::XMLDocument TMXDocument;
	tinyxml2::XMLError errorHandler;

	errorHandler = TMXDocument.LoadFile(filePath); 

	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED)
	{
		return false;
	}

	tinyxml2::XMLElement* mapNode = TMXDocument.FirstChildElement("map");

	if (mapNode == nullptr)
	{
		return false;
	}

	//Set width and height for the tilemap.
	SetWidth(mapNode->FloatAttribute("width"));
	SetHeight(mapNode->FloatAttribute("height"));

	//Create the tilemap.
	CreateTilemap();

	//Set the width and height for the tiles.
	tileWidth = mapNode->FloatAttribute("tilewidth");
	tileHeight = mapNode->FloatAttribute("tileheight");

	// Loading Tilset element
	tinyxml2::XMLElement* TMXTileset = mapNode->FirstChildElement("tileset");

	if (TMXTileset == NULL)
	{
		return false;
	}

	//***********************************************************************************************************************
	//Load TSX file.
	string TSXpath = "res/Tilemap/";
	TSXpath += TMXTileset->Attribute("source");

	tinyxml2::XMLDocument TSXDocument; 
	tinyxml2::XMLError errorHandler2;

	errorHandler2 = TSXDocument.LoadFile(TSXpath.c_str());

	if (errorHandler2 == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler2 == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED)
	{
		return false;
	}

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement* TSXTileset = TSXDocument.FirstChildElement("tileset");

	if (TSXTileset == NULL)
	{
		return false;
	}

	// Save the Tiles in the TileMap
	imageWidth = TSXTileset->FirstChildElement("image")->IntAttribute("width");
	imageHeight = TSXTileset->FirstChildElement("image")->IntAttribute("height");

	//***********************************************************************************************************************

	imagePath = "res/Tilemap/";
	imagePath += TSXTileset->FirstChildElement("image")->Attribute("source");

	//Number of Tiles in the tileset
	int tileCount = TSXTileset->IntAttribute("tilecount");

	//Columns of Tiles in the tileset
	int columns = TSXTileset->IntAttribute("columns");

	//Rows in the tileset
	int rows = tileCount / columns;

	float tileX = 0.0f, tileY = 0.0f;
	int id = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Tile newTile;

			newTile.SetID(id);

			//TODO: Pasar los parametros correctos de cada Tile.
			newTile.SetSprite(imagePath.c_str(), defaultColor, render, defaultPosition, defaultScale, defaultRotation);

			tileX += tileWidth;
			AddTile(newTile);
			id++;
		}

		tileX = 0;
		tileY += tiles[i].GetHeight();
	}

	tinyxml2::XMLElement* pTile = TSXTileset->FirstChildElement("tile");

	while (pTile)
	{
		unsigned int id = pTile->IntAttribute("id");

		tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");

		string propertyName = pProperty->Attribute("value");

		if (propertyName == "false")
		{
			tiles[id].SetCollision(false);
		}

		else
		{
			tiles[id].SetCollision(true);
		}

		pTile = pTile->NextSiblingElement("tile");
	}

	// Loading Layer element
	tinyxml2::XMLElement* layer = mapNode->FirstChildElement("layer");
	if (layer == NULL)
	{
		return false;
	}

	int layerCount = 0;

	while (layer)
	{
		// Loading Data element
		tinyxml2::XMLElement* data = layer->FirstChildElement("data");

		if (data == NULL)
		{
			return false;
		}

		if (layerCount > 0)
		{
			Tile** auxTileMap;
			auxTileMap = new Tile * [height];

			for (int i = 0; i < height; i++)
			{
				auxTileMap[i] = new Tile[width];
			}

			tilemap.push_back(auxTileMap);
		}

		while (data)
		{
			std::vector<int> tileGids;

			for (tinyxml2::XMLElement* pTile = data->FirstChildElement("tile");
				pTile != NULL;
				pTile = pTile->NextSiblingElement("tile"))
			{
				unsigned int gid = std::atoi(pTile->Attribute("gid")); // tile's id is saved
				tileGids.push_back(gid);
			}

			int gid = 0;

			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (tileGids[gid] != 0)
					{
						SetTileInTilemap(layerCount, y, x, tileGids[gid]);
					}

					gid++;
				}
			}

			data = data->NextSiblingElement("data");
		}

		layerCount++;
		layer = layer->NextSiblingElement("layer");
	}

	return true;
}


void Tilemap::Draw()
{
	float mapWidth = -(width * tileWidth) / 2;
	float mapHeight = (height * tileHeight) / 2;

	for (int i = 0; i < tilemap.size(); i++) 
	{	
		for (int y = 0; y < height; y++) 
		{		
			for (int x = 0; x < width; x++) 
			{
				if (tilemap[i][y][x].GetID() != NULL) {
					tilemap[i][y][x].GetSprite()->setPosition(Vector3{ mapWidth + (tileWidth * x), mapHeight - (tileHeight * y), 0});
					tilemap[i][y][x].GetSprite()->Draw();
				}
			}
		}
	}
}

//TODO: Finish collision
void Tilemap::CheckCollision(Entity2D* entity)
{

}
