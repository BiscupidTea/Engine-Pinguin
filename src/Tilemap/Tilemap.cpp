#include "Tilemap.h"
#include "Tilemap/tinyxml2.h"

using namespace tinyxml2;

Tilemap::Tilemap(const char* tileSetFile, const vector<const char*>& tileMapFiles, const char* tileMapImage,
	             Vector4 rgba, Renderer* renderer, Vector3 newPosition, Vector3 newScale, Vector3 newRotation) 
	           : Entity2D(rgba, renderer, newPosition, newScale, newRotation)
{
	LoadTileSet(tileSetFile);

	for (int i = 0; i < tileMapFiles.size(); i++)
	{
		layers.emplace_back(new TilemapLayer(tileMapFiles.at(i), tileMapImage, tileSet, rgba, renderer, newPosition, 
			                                 newScale, newRotation));
	}
}

Tilemap::~Tilemap()
{
	for (TilemapLayer* layer : layers)
	{
		delete layer;
	}

	layers.clear();
}

void Tilemap::LoadTileSet(const char* tileSetFile)
{
	XMLDocument doc;
	if (doc.LoadFile(tileSetFile) != XML_SUCCESS)
	{
		cout << "Error loading file XML: " << tileSetFile << endl;
		return;
	}

	XMLElement* root = doc.FirstChildElement("tileset");
	if (!root)
	{
		cout << "Error: file is not a tileset file" << endl;
		return;
	}

	root->QueryIntAttribute("tilewidth", &tilePixelWidth);
	root->QueryIntAttribute("tileheight", &tilePixelHeight);

	root = doc.FirstChildElement("tileset")->FirstChildElement("image");
	root->QueryIntAttribute("width", &mapPixelWidth);
	root->QueryIntAttribute("height", &mapPixelHeight);

	tileSetTileHeight = (mapPixelHeight / tilePixelHeight);
	tileSetTileWidth = (mapPixelWidth / tilePixelWidth);

	vector<vector<vec2>> tileSetUV = CalculateUVCoordsInMap(tileSetTileHeight, tileSetTileWidth, 
		                                                    mapPixelHeight, mapPixelWidth, tilePixelHeight, tilePixelWidth);

	root = doc.FirstChildElement("tileset");

	XMLElement* tileElement = root->FirstChildElement("tile");
	while (tileElement)
	{
		int tileId = tileElement->IntAttribute("id");
		bool hasCollision = false;

		XMLElement* properties = tileElement->FirstChildElement("properties");
		if (properties)
		{
			XMLElement* property = properties->FirstChildElement("property");
			while (property)
			{
				const char* name = property->Attribute("name");
				if (name && strcmp(name, "Obstacle") == 0)
				{
					const char* value = property->Attribute("value");
					if (value && strcmp(value, "true") == 0)
					{
						hasCollision = true;
						break;
					}
				}
				property = property->NextSiblingElement("property");
			}
		}

		tileSet.push_back(Tile(tileId, hasCollision, tileSetUV.at(tileId)));
		tileElement = tileElement->NextSiblingElement("tile");
	}
	cout << "Loaded " << tileSet.size() << " tiles" << endl;
	cout << endl;
}

void Tilemap::Draw()
{
	for (TilemapLayer* layer : layers)
	{
		layer->Draw();
	}
}

vector<vector<vec2>> Tilemap::CalculateUVCoordsInMap(int heightTiles, int widthTiles, int totalHeight, int totalWidth, int tileHeight, int tileWidth)
{
	vector<vector<vec2>> uvCoordsList;

	int padding = 0;

	for (int y = 0; y < heightTiles; ++y)
	{
		for (int x = 0; x < widthTiles; ++x)
		{
			vector<vec2> uvCoords;

			//topLeft
			uvCoords.push_back(vec2(static_cast<float>((x * tileWidth) + padding * x) / totalWidth,
				               1.0f - static_cast<float>((y * tileHeight) + padding * y) / totalHeight));
			
			//TopRight
			uvCoords.push_back(vec2(static_cast<float>(((x + 1) * tileWidth) + padding * x) / totalWidth,
				               1.0f - static_cast<float>((y * tileHeight) + padding * y) / totalHeight));
			
			//BottomLeft
			uvCoords.push_back(vec2(static_cast<float>((x * tileWidth) + padding * x) / totalWidth,
				               1.0f - static_cast<float>(((y + 1) * tileHeight) + padding * y) / totalHeight));
			
			//BottomRight
			uvCoords.push_back(vec2(static_cast<float>(((x + 1) * tileWidth) + padding * x) / totalWidth,
			                   1.0f - static_cast<float>(((y + 1) * tileHeight) + padding * y) / totalHeight));

			uvCoordsList.push_back(uvCoords);
		}
	}

	return uvCoordsList;
}