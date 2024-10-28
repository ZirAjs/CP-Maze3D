#include "Map.h"
#include "Map.h"

namespace Engine
{

    Map::Map(std::vector<std::vector<int>>& map):map(map)
    {
    }
    Map::Map(std::vector<std::vector<int>>&& m):map(m)
    {
    }


    Map::~Map() = default;

    std::pair<int, int> Map::GetMapCoord(const float& x, const float& y) {
        return std::pair<int, int>((int)std::floor(x), (int)std::floor(y));
    }

    std::pair<int, int> Map::GetMapCoord(const Vector& v) {
        return std::pair<int, int>((int)std::floor(v.x), (int)std::floor(v.y));
    }

    /// <summary>
    /// checks if point is inside a wall. returns true if it is and otherwise false.
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    Map::RoomState Map::IsPointInWall(Vector v)
    {
        auto mapCoord = GetMapCoord(v);
        return static_cast<RoomState>(map[mapCoord.second][mapCoord.first]);
        //switch ()
        //{
        //case 0:
        //	return RoomState::empty;
        //case 1:
        //	return RoomState::wall;
        //case 2:
        //	return RoomState::start;
        //case 3:
        //	return RoomState::end;
        //default:
        //	// error
        //	return RoomState::error;
        //}
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
        int testYcoord = (int)std::floor(r.pos.y - r.direction.y * (std::abs(std::floor(r.pos.x) - r.pos.x + (r.direction.x < 0))) / r.direction.x);
        if (ycoord == testYcoord)
        {
            return Vector(1, 0, 0);
        }
        return Vector(0, 1, 0);
    }

    /// <summary>
    /// returns the starting point of the map
    /// </summary>
    /// <returns></returns>
    Vector Map::GetStartPoint()
    {
        
        for (int y = 0; y < map.size(); y++)
        {
            for (int x = 0; x < map[y].size(); x++)
            {
                // if starting point
                if (map[y][x] == RoomState::start)
                {
                    return Vector((float)x, (float)y, 0.5f);
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
        for (int y = 0; y < map.size(); y++)
        {
            for (int x = 0; x < map[y].size(); x++)
            {
                // if ending point
                if (map[y][x] == RoomState::end)
                {
                    return Vector((float)x, (float)y, 0.5f);
                }
            }
        }
        return Vector(-1, -1, -1);
    }


    Light Map::GetLight(Ray ray)
    {
        auto mapCoord = GetMapCoord(ray.direction+ray.pos);
        switch (map[mapCoord.first][mapCoord.second])
        {
        case RoomState::wall:
            return Light(std::string("white"), GetWallNormalVector(ray));

        case RoomState::end:
            return Light(std::string("blue"), GetWallNormalVector(ray));

        case RoomState::start:
            return Light(std::string("yellow"), GetWallNormalVector(ray));

        case RoomState::empty:
            return Light(std::string("black"), GetWallNormalVector(ray));
            
        default:
            throw std::runtime_error("Error: Invalid room state");
        }
    }
}