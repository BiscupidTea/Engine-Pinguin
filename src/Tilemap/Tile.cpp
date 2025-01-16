#include "Tile.h"

Tile::Tile()
{
	ID = 0;
	hasCollision = false;

	width = 16.0f;
	height = 16.0f;
}

Tile::~Tile()
{
}

void Tile::SetID(int value)
{
	ID = value;
}

int Tile::GetID()
{
	return ID;
}

void Tile::SetCollision(bool value)
{
	hasCollision = value;
}

bool Tile::GetCollision()
{
	return hasCollision;
}

void Tile::SetWidth(float value)
{
	width = value;
}

float Tile::GetWidth()
{
	return width;
}

void Tile::SetHeight(float value)
{
	height = value;
}

float Tile::GetHeight()
{
	return height;
}

void Tile::SetSprite(const char* textureName, Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation)
{
	sprite = new Sprite(textureName, rgba, render, newPosition, newScale, newRotation);
}

Sprite* Tile::GetSprite()
{
	return sprite;
}
