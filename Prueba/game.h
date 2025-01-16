#pragma once
#include "CoreEngine/BaseGame.h"

using namespace baseEngine;

class Game : public BaseGame
{
private:
	const char* windowName;
	Sprite* Letter;
	Sprite* BackGround;
	Sprite* Player;

	Tilemap* tilemap;

	Vector3 lastTexturePos;

	Vector4 ShaperColor;
	Vector3 ShapePosition;
	Vector3 ShaperScale;
	Vector3 ShapeRotation;

	Vector4 TextureColor;
	Vector3 BackgroundPos;
	Vector3 BackgroundScale;
	Vector3 TextureRotation;

	Vector3 PlayerPos;

	Vector4 TextureColor2;
	Vector3 TexturePosition2;
	Vector3 TextureScale2;
	Vector3 TextureRotation2;

	Animation* idleAnimation;
	Animation* BackgroundAnimation;
	Animation* runAnimation;
	Animation* playerIdle;

public:
	float width;
	float height;

	Game(float width, float height, const char* windowName);
	~Game();
	void init() override;
	void update() override;
	void exit() override;
};