#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "GameUtility.h"
#include "Renderable.h"

namespace Engine
{

    class Map
    {
    public:
        Map();
        Map(std::vector<std::vector<int>>& map);
        Map(std::vector<std::vector<int>>&& map);
        ~Map();


        // state
        enum RoomState {
            empty=0,
            wall=1,
            start=2,
            end=3,
            object = 10,
            error=10
        };

        // get the state of the point
        std::pair<int, int> GetMapCoord(const float& x, const float& y);
        std::pair<int, int> GetMapCoord(const Vector& v);


        Map::RoomState IsPointInWall(Vector);
        Vector GetWallNormalVector(Ray);
        Vector GetStartPoint();
        Vector GetEndPoint();

        Light GetLight(Ray ray);

    private:
        /*const int room_empty = 0;
        const int room_wall = 1;
        const int room_start = 2;
        const int room_end = 3;*/


        // 0= empty
        // 1= wall<
        // 2= start point (hard-coded currently) => fixed
        // 3= end point
        std::vector<std::vector<int>> map;

    };
}
