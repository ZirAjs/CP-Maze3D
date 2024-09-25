#include "Map.h"

namespace maze
{
	Map::Map()
	{
		//do nothing
	}
	// Map
	Map::Map(std::string map)
	{
	}

	Map::~Map()
	{
	}

	/// <summary>
	/// checks if point is inside a wall. returns true if it is and otherwise false.
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	bool Map::IsPointInWall(Vector v)
	{
		switch (map[(int)std::floor(v.y)][(int)std::floor(v.x)])
		{
		case 0:
		case 2:
			return false;
		case 1:
			return true;
		default:
			// error
			return true;
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
}