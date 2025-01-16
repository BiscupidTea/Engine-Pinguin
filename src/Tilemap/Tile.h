#pragma once

#include "Tools/dll-Exp-Inp.h"
#include "Entity/Sprite.h"

using namespace sprite;

class EXPORT Tile
{
private:

	int ID;
	bool hasCollision;

	float width;
	float height;

	Sprite* sprite;

public:

	Tile();
	~Tile();

	void SetID(int value);
	int GetID();

	void SetCollision(bool value);
	bool GetCollision();

	void SetWidth(float value);
	float GetWidth();

	void SetHeight(float value);
	float GetHeight();

	void SetSprite(const char* textureName, Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
	Sprite* GetSprite();
};

