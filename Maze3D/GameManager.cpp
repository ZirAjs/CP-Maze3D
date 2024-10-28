#include "GameManager.h"

// TODO state how coordinates are managed. top left is zero.
// In order for this to work, angle should increase in right arrow direction. i.e. theta' = -theta.

namespace maze
{
	GameManager::GameManager()
	{
		// gameObjects
		map = new Map(std::vector<std::vector<int>> {
			{ 1,1,1,1,1,1,1,1,1,1 },
			{ 1,2,0,0,0,0,1,0,0,1 },
			{ 1,1,0,1,1,1,1,1,0,1 },
			{ 1,0,0,0,0,0,0,1,0,1 },
			{ 1,0,1,1,1,1,0,0,0,1 },
			{ 1,0,1,0,0,0,0,1,0,1 },
			{ 1,0,1,0,1,0,1,0,1,1 },
			{ 1,0,1,3,1,0,0,0,0,1 },
			{ 1,0,1,1,1,1,1,1,0,1 },
			{ 1,1,1,1,1,1,1,1,1,1 },
		});
		player = new Player(map->GetStartPoint() + Engine::Vector(0.5f, 0.5f, 0));
		camera = new Camera(Engine::Vector::Zero(), 0.0f, player);
		renderables.push_back(new Box(Engine::Vector(1,3,0.2f), Engine::Vector(1,1,1), 0));
		renderer = new Renderer(renderables, *map, *camera);
		
		renderer->InitConsole();
	}

	GameManager::~GameManager() {
		delete map;
		delete player;
		delete camera;
		delete renderer;

		for (auto& r : renderables)
		{
			delete r;
		}
	}
	

	/// <summary>
	/// Starts the Mainloop.
	/// </summary>
	void GameManager::Mainloop()
	{

		// render initial screen
		renderer->Render();

		// move helper function
		auto moveHelper = [&](float angleOffset)
		{
			return Engine::Vector(
				std::cos(player->transform->GetLocalAngle() + angleOffset) * player->speedFactor * 1,
				std::sin(player->transform->GetLocalAngle() + angleOffset) * player->speedFactor * 1,
				0);
		};

		// store user input
		int uInput;
		// 27 == "ESC"
		while ((uInput = _getch()) != KEY_ESC)
		{
			// special keycode begin with 0 or 224

			// handle movement
			if (uInput == 0 || uInput == 224)
			{
				// movement destination
				Engine::Vector dest = player->transform->GetWorldPos();
				// 72 (up), 80 (down), 75 (left) and 77 (right)
				switch (uInput = _getch())
				{
				case KEY_UP: // up
					dest += moveHelper(0);
					break;
				case KEY_DOWN: // down
					dest += moveHelper(Pi);
					break;
				case KEY_LEFT: // left
					dest += moveHelper(-Pi / 2);
					break;
				case KEY_RIGHT: // right
					dest += moveHelper(Pi / 2);
					break;
				}

				// apply movement when dest is not inside the map
				if (map->IsPointInWall(dest) != Engine::Map::wall)
				{
					// apply movement
					player->transform->SetPosition(dest);
				}
			}
			else
			{
				// handle rotation
				switch (uInput)
				{
				case '.': // right
					// rotate right
					// this is because the coordinate system is different from the one used in the renderer.
					// that's why the angle is positive.
					player->transform->AddAngle(player->rotationFactor);
					break;
				case ',': // left
					// rotate left
					player->transform->AddAngle(-player->rotationFactor);
					break;
				}
				// handle rotation
			}
			// render
			renderer->Render();

			// DEBUG
			// DBOUT("angle: " << player->getDirection()/Pi<< "pi\n")
		}
		// exit with esc
	}

	
}
