#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GameMath.h"

namespace maze
{
	constexpr int mapX = 10;
	constexpr int mapY = 10;

	class Map
	{
	public:
		Map();
		~Map();

		// state
		static enum PointState
		{
			wall,
			start,
			end,
			empty
		};

		Map::PointState IsPointInWall(Vector);
		Vector GetWallNormalVector(Ray);
		Vector GetStartPoint();
		Vector GetEndPoint();




	private:

		const int room_empty = 0;
		const int room_wall = 1;
		const int room_start = 2;
		const int room_end = 3;

		// 0= empty
		// 1= wall
		// 2= start point (hard-coded currently)
		// 3= end point
		int map[mapY][mapX] = {
		1,1,1,1,1,1,1,1,1,1,
		1,2,0,0,0,0,1,0,1,1,
		1,1,1,1,1,0,1,0,1,1,
		1,0,0,0,0,0,0,0,1,1,
		1,0,1,0,1,1,1,0,0,1,
		1,1,1,0,0,1,1,1,0,1,
		1,1,1,1,0,0,1,0,0,1,
		1,1,3,1,1,1,0,0,1,1,
		1,0,0,0,0,0,0,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		};
	};
}
