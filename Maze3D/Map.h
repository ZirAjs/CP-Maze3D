#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GameMath.h"

namespace maze
{

	class Map
	{
	public:
		Map();
		Map(std::string);
		~Map();
		bool IsPointInWall(Vector);
		Vector GetWallNormalVector(Ray);


	private:
		// 0= empty
		// 1= wall
		// 2= start point (hard-coded currently)
		int map[10][10] = {
		1,1,1,1,1,1,1,1,1,1,
		1,2,0,0,0,0,1,0,1,1,
		1,1,1,1,1,0,1,0,1,1,
		1,0,0,0,0,0,0,0,1,1,
		1,0,1,0,1,1,1,0,1,1,
		1,0,1,0,0,1,1,0,1,1,
		1,0,1,1,0,0,1,0,1,1,
		1,0,1,1,1,0,1,0,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		};
	};
}
