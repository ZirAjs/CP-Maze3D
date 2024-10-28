#pragma once
#include <string>
#include <conio.h>
#include <cmath>
#include <string>
#include <map>
#include "Player.h"
#include "Box.h"
#include "GameEngine/Map.h"
#include "GameEngine/GameUtility.h"
#include "GameEngine/Renderer.h"
#include "GameEngine/Renderable.h"
#include "GameEngine/Camera.h"
#include "GameEngine/EngineTypes.h"

#if _DEBUG
#define DBOUT( s )			\
{							\
	std::ostringstream os_;	\
	os_ << s;				\
	OutputDebugStringA(os_.str().c_str()); \
}
#endif
// #define DBOUT( s )			\
//{							\
//	std::ostringstream os_;	\
//	os_ << s;				\
//	OutputDebugStringA(os_.str().c_str()); \
//}

namespace maze
{

	// alias
	//template <typename T>
	//using uPtr = std::unique_ptr<T>;
	using Map = Engine::Map;
	using Renderer = Engine::Renderer;
	using Camera = Engine::Camera;
	constexpr const float& Pi = Engine::Pi;


	constexpr int KEY_ESC = 27; // Escape key
	constexpr int KEY_UP = 72;  // Up arrow key
	constexpr int KEY_DOWN = 80; // Down arrow key
	constexpr int KEY_LEFT = 75; // Left arrow key
	constexpr int KEY_RIGHT = 77; // Right arrow key

	class GameManager
	{

	public:
		// Constuctor&Deconstructor
		GameManager();
		~GameManager();

		// methods
		void Mainloop();

	private:

		// renderer
		Renderer* renderer;

		// camera
		Camera* camera;

		// new player
		Player* player;

		// game map
		Map* map;

		// objects for demonstration
		Engine::Renderer::renderables_t renderables{};
	};
}