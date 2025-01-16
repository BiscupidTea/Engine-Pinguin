#pragma once
#include "CoreEngine/Window.h"
#include "CoreEngine/Renderer.h"

#include "Entity/Shape.h"
#include "Entity/Sprite.h"

#include "Tilemap/Tilemap.h"

#include "Tools/dll-Exp-Inp.h"
#include "Tools/Time.h"
#include "Tools/CollisionManager.h"
#include "InputSystem.h"

using namespace shape;
using namespace window;
using namespace renderer;
using namespace sprite;
using namespace collisionManager;
using namespace inputSystem;

namespace baseEngine
{
	/// <summary>
	/// Class BaseGame
	/// </summary>
	class EXPORT BaseGame
	{
	private:

		Renderer* renderer;
		Window* window;
		ErrorLog errorLog;

	public:

		InputSystem* inputSystem;
		BaseGame(int width, int height, const char* windowName);
		~BaseGame();
		void gameLoop();
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void exit() = 0;
		Renderer* GetRenderer();
	};
}