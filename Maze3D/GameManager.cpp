#include "GameManager.h"

// TODO state how coordinates are managed. top left is zero.
// In order for this to work, angle should increase in right arrow direction. i.e. theta' = -theta.
namespace maze
{
	GameManager::GameManager()
	{
		InitConsole();
		player = new Player(map.GetStartPoint() + Vector(0.5f, 0.5f, 0));
	}

	GameManager::~GameManager()
	{
		delete player;
	}

	/// <summary>
	/// Starts the Mainloop.
	/// </summary>
	void GameManager::Mainloop()
	{

		// render initial screen
		Render();

		// store user input
		int uInput;

		// 27 == "ESC"
		while ((uInput = _getch()) != 27) {
			// special keycode begin with 0 or 224


			// handle movement
			if (uInput == 0 || uInput == 224) {
				// movement destination
				Vector dest = player->pos;
				// 72 (up), 80 (down), 75 (left) and 77 (right)
				switch (uInput = _getch())
				{
				case 72: // up
					dest += Vector(
						std::cos(player->getDirection()) * player->speedFactor * 1,
						std::sin(player->getDirection()) * player->speedFactor * 1,
						0
					);
					break;
				case 80: // down
					dest += Vector(
						std::cos(player->getDirection() + Pi) * player->speedFactor * 1,
						std::sin(player->getDirection() + Pi) * player->speedFactor * 1,
						0
					);
					break;
				case 75: //left
					dest += Vector(
						std::cos(player->getDirection() + 3 * Pi / 2) * player->speedFactor * 1,
						std::sin(player->getDirection() + 3 * Pi / 2) * player->speedFactor * 1,
						0
					);
					break;
				case 77: // right
					dest += Vector(
						std::cos(player->getDirection() + Pi / 2) * player->speedFactor * 1,
						std::sin(player->getDirection() + Pi / 2) * player->speedFactor * 1,
						0
					);
					break;
				}

				// apply movement when dest is not inside the map
				if (map.IsPointInWall(dest)!=Map::wall) {
					// apply movement
					player->pos = dest;
				}
			}
			else {
				// handle rotation
				switch (uInput) {
					case '.':	//right
						// rotate right
						player->addDirection(-player->rotationFactor);
						break;
					case ',':	//left
						// rotate left
						player->addDirection(player->rotationFactor);
						break;
				}
				// handle rotation
			}
			// render
			Render();

			// DEBUG
			// DBOUT("angle: " << player->getDirection()/Pi<< "pi\n")
		}
		// exit with esc
	}

	/// <summary>
	/// Initialize the console by setting buffer size and fetching screen information(i.e. buffer)
	/// </summary>
	void GameManager::InitConsole() {
		// init hOut
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// set buffersize
		SetConsoleScreenBufferSize(hOut, consoleSize);
		GetCsbi();
	}

	/// <summary>
	/// Get Console screen buffer info
	/// </summary>
	void GameManager::GetCsbi()
	{
		if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
			throw std::exception("Cannot fetch console info");
		}
	}

	/// <summary>
	/// Renders screen. Calculates each pixcel and Draws if changes are made.
	/// Calculations are described in the report
	/// </summary>
	void GameManager::Render()
	{
		// x,y 잘못 씀. 배열에서 [row][col]임.
		for (short y = 0; y < CONSOLE_Y; y++)
		{
			// set y as a coordinate in camera plane
			float camY = (CONSOLE_Y / 2 - y) / float(CONSOLE_Y) * camPlaneY;
			for (short x = 0; x < CONSOLE_X; x++) {
				// set x as a coordinate in camera plane
				float camX = (x - CONSOLE_X / 2) / float(CONSOLE_X) * camPlaneX;

				// matrix mutiplication
				Vector dir(camZ * std::cos(player->getDirection()) - camX * std::sin(player->getDirection()),
					camZ * std::sin(player->getDirection()) + camX * std::cos(player->getDirection()),
					camY - yDirOffset);
				Ray r(player->pos + dir, Vector::Normalize(dir));


				// used to store previous point state. inorderto color the room correctly.
				Map::PointState tempPointState = Map::empty;

				// raycast...no possibility of 'Failed to raycast'
				for (int i = 1; i < 1000; i++)
				{
					// point to test
					Vector test = r.pos + r.direction * stepSize * i;
					//test result
					Map::PointState pointState = map.IsPointInWall(test);

					if (test.z <= 0) {
						// I = (raydir dotproduct normalvector) * I0 / (r**2)
						float brightness = std::abs(Vector::InnerProduct(r.direction, Vector(0, 0, 1)) * LIGHT_INTENSITY / std::pow((stepSize * i), 2));

						// match brightness
						consoleScreen[y][x] = MatchAscii(brightness);
						consoleScreenColor[y][x] = colorMap.at(tempPointState);
						break;
					}
					else if (test.z >= 1) {
						// I = (raydir dotproduct normalvector) * I0 / (r**2)
						float brightness = std::abs(Vector::InnerProduct(r.direction, Vector(0, 0, -1)) * LIGHT_INTENSITY / std::pow((stepSize * i), 2));

						// match brightness
						consoleScreen[y][x] = MatchAscii(brightness);
						consoleScreenColor[y][x] = colorMap.at(tempPointState);
						break;
					}
					else if (pointState==Map::PointState::wall) {
						// I = (raydir dotproduct normalvector) * I0 / (r**2)
						float brightness = std::abs(Vector::InnerProduct(r.direction, map.GetWallNormalVector(Ray(test, r.direction))) * LIGHT_INTENSITY / std::pow((stepSize * i), 2));

						// match brightness
						consoleScreen[y][x] = MatchAscii(brightness);
						consoleScreenColor[y][x] = colorMap.at(tempPointState);
						break;
					}
					tempPointState = pointState;
				}
			}
		}

		// draw the screen
		DrawConsoleScreen();
	}

	/// <summary>
	/// Draw individual pixel. 
	/// </summary>
	/// <param name="coord"></param>
	/// <param name="value"></param>
	void GameManager::DrawPixel(COORD coord, char value) const
	{
		SetConsoleCursorPosition(hOut, coord);
		std::cout << value << std::flush;
	}

	/// <summary>
	/// Draw 'consoleScreen' via console
	/// </summary>
	void GameManager::DrawConsoleScreen()
	{
		std::ostringstream screenStream;
		// build string
		for (int y = 0; y < CONSOLE_Y; y++) {
			for (int x = 0; x < CONSOLE_X; x++)
			{
				screenStream << consoleScreenColor[y][x] << consoleScreen[y][x];
			}
			screenStream << '\n';
		}

		SetConsoleCursorPosition(hOut, COORD{ 0,0 });
		std::cout << screenStream.str() << std::flush;
	}

	/// <summary>
	/// finds the ascii character corresponding to the given brightness
	/// </summary>
	/// <param name="brightness"></param>
	/// <returns></returns>
	char GameManager::MatchAscii(float brightness)
	{


		// DBOUT("debug: " << i << std::endl)
		//DBOUT("step: "<<i<<"\n")
		//DBOUT("brightness: " << brightness << "\n")

		// FOR DEVELOPEMENT 거리를 먼저 나타냅시다.
		//brightness = (int)((stepSize * i) * 1000);


		// brightness table 
		char pixel = ' ';
		if (900 < brightness) {
			pixel = '@';
		}
		else if (800 < brightness && brightness <= 900) {
			pixel = '#';
		}
		else if (700 < brightness && brightness <= 800) {
			pixel = 'b';
		}
		else if (600 < brightness && brightness <= 700) {
			pixel = '0';
		}
		else if (500 < brightness && brightness <= 600) {
			pixel = 'Y';
		}
		else if (400 < brightness && brightness <= 500) {
			pixel = 'x';
		}
		else if (300 < brightness && brightness <= 400) {
			pixel = '|';
		}
		else if (200 < brightness && brightness <= 300) {
			pixel = ';';
		}
		else if (100 < brightness && brightness <= 200) {
			pixel = '.';
		}
		else if (0 <= brightness && brightness <= 100) {
			pixel = ' ';
		}
		else
		{
			//Debug
			//DBOUT("brightness: " << brightness << "\n")
		}
		return pixel;
	}
}

