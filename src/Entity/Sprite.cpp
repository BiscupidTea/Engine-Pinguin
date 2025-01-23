#include "Entity/Sprite.h"

namespace sprite
{
	Sprite::Sprite(const char* textureName, Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation) : Entity2D(rgba, render, newPosition, newScale, newRotation)
	{
		CreateSprite();

		render->CreateVBuffer(vertexPositions, indexs, vertexSize, indexSize, atributeVertexSize, VAO, VBO, EBO, aColorSize, aUvSize);
		render->BindTexture(textureName, textureId);
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::CreateSprite()
	{
		vertexSize = 36;

		vertexPositions = new float [vertexSize]
		{
			// positions		 // colors						// texture coords
			0.5f, 0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,   // bottom left
			-0.5f, 0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f    // top left 
		};

		indexSize = 6;
		indexs = new int[indexSize]
		{
			0, 1, 3,
			1, 2, 3
		};
	}

	void Sprite::Update()
	{
		if (!animation)
		{
			return;
		}
		else
		{
			animation->UpdateAnimation();
			SetUV(animation->GetFrames()[animation->GetCurrentFrame()]);
		}
	}

	void Sprite::Draw()
	{
		DrawTexture(textureId);
	}

	void Sprite::SetAnimation(Animation* animation)
	{
		this->animation = animation;
	}

	void Sprite::SetUV(Frame frame)
	{
		vertexSize = 36;

		vertexPositions = new float [vertexSize]
		{
			// positions		 // colors					// texture coords
			-0.5f, -0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,	frame.uvArray[0].u, frame.uvArray[0].v,   // bottom left
			0.5f, -0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,	frame.uvArray[1].u, frame.uvArray[1].v,   // bottom right
			-0.5f, 0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,	frame.uvArray[2].u, frame.uvArray[2].v,    // top left 
			0.5f, 0.5f, 0.0f,	 1.0f, 1.0f, 1.0f, 1.0f,	frame.uvArray[3].u, frame.uvArray[3].v   // top right
		};

		indexSize = 6;
		indexs = new int[indexSize]
		{
			0, 1, 2,
			1, 2, 3
		};

		render->CreateVBuffer(vertexPositions, indexs, vertexSize, indexSize, atributeVertexSize, VAO, VBO, EBO, aColorSize, aUvSize);
	}

}