#include "Map.h"

namespace maze
{
	Map::Map()
	{
		//do nothing
	}

	Map::~Map()
	{
	}

	/// <summary>
	/// checks if point is inside a wall. returns true if it is and otherwise false.
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	Map::PointState Map::IsPointInWall(Vector v)
	{
		switch (map[(int)std::floor(v.y)][(int)std::floor(v.x)])
		{
		case 0:
			return PointState::empty;
		case 1:
			return PointState::wall;
		case 2:
			return PointState::start;
		case 3:
			return PointState::end;
		default:
			// error
			return PointState::wall;
		}
	}

	/// <summary>
	/// returns normal vector of the wall that has been collided with given Ray.
	/// </summary>
	/// <param name="r"></param>
	/// <returns></returns>
	Vector Map::GetWallNormalVector(Ray r)
	{
		// prepare ycoordinate of the wall.
		int ycoord = (int)std::floor(r.pos.y);

		// test logic. explained in the report
		int testYcoord = (int)std::floor(r.pos.y-r.direction.y*(std::abs(std::floor(r.pos.x)- r.pos.x + (r.direction.x < 0))) / r.direction.x);
		if (ycoord == testYcoord) {
			return Vector(1, 0, 0);
		}
		return Vector(0,1,0);
	}

	/// <summary>
	/// returns the starting point of the map
	/// </summary>
	/// <returns></returns>
	Vector Map::GetStartPoint()
	{
		for (int y = 0; y < mapY; y++)
		{
			for (int x = 0; x < mapX; x++)
			{
				// if starting point
				if (map[y][x]==room_start) {
					return Vector(x, y, 0.5f);
				}
			}
		}
		return Vector(-1, -1, -1);
	}

	/// <summary>
	/// returns the ending point of the map
	/// </summary>
	/// <returns></returns>
	Vector Map::GetEndPoint()
	{
		for (int y = 0; y < mapY; y++)
		{
			for (int x = 0; x < mapX; x++)
			{
				// if starting point
				if (map[y][x] == room_end) {
					return Vector(x, y, 0.5f);
				}
			}
		}
		return Vector(-1, -1, -1);
	}
}