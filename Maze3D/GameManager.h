#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>
#include <sstream>
#include <string>
#include <map>
#include "Player.h"
#include "Map.h"
#include "GameMath.h"


//for debug
//#define DBOUT( s )			\
//{							\
//	std::ostringstream os_;	\
//	os_ << s;				\
//	OutputDebugStringA(os_.str().c_str()); \
//}




namespace maze
{
	// define console ratio
	// (18x36x16) x (36x18x9) 16:9¿¡ °¡±õµµ·Ï
	// cursor size
	constexpr int CURSOR_X = 18;
	constexpr int CURSOR_Y = 36;

	//288:81->144:40
	constexpr int CONSOLE_X = 144;
	constexpr int CONSOLE_Y = 40;


	class GameManager
	{

	public:
		// Constuctor&Deconstructor
		GameManager();
		~GameManager();

		//methods
		void Mainloop();

	private:
		// fields

		// new player
		Player* player;

		// game map
		Map map;

		// console handle
		HANDLE hOut;

		// console size
		const COORD consoleSize{ CONSOLE_X,CONSOLE_Y };
		// CONSOLE_Y x CONSOLE_X
		char consoleScreen[CONSOLE_Y][CONSOLE_X] = {};
		std::string consoleScreenColor[CONSOLE_Y][CONSOLE_X] = {};

		CONSOLE_SCREEN_BUFFER_INFO csbi;

		// rendering options
		int LIGHT_INTENSITY = 300;
		float camPlaneX = 0.16;
		float camPlaneY = 0.09;
		float camZ = 0.1;
		float stepSize = 0.02;
		float yDirOffset = 0.03f;

		// color table
		const std::map<Map::PointState, std::string> colorMap = { {Map::PointState::wall, "\033[39m"},
			{Map::PointState::empty, "\033[39m"} ,
			{Map::PointState::start, "\033[34m"} ,
			{Map::PointState::end, "\033[33m"} };


		// methods
		void InitConsole();
		void GetCsbi();
		void Render();
		void DrawConsoleScreen();
		char MatchAscii(float brightness);

		// Not Used
		void DrawPixel(COORD, char) const;
	};
}