#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include "Renderable.h"
#include "Camera.h" 
#include "GameUtility.h"
#include "Object.h"
#include "Map.h"
#include "EngineTypes.h"

#if _DEBUG
#define DBOUT( s )			\
{							\
    std::ostringstream os_;	\
    os_ << s;				\
    OutputDebugStringA(os_.str().c_str()); \
}
#endif

namespace Engine
{

    // define console ratio
    // (18x36x16) x (36x18x9) 16:9 ratio
    // cursor size
    constexpr int CURSOR_X = 18;
    constexpr int CURSOR_Y = 36;

    // 288:81->144:40
    constexpr int CONSOLE_X = 144;
    constexpr int CONSOLE_Y = 40;

    class Renderer
    {
    public:
        
        // alias
        using renderables_t = std::vector<const Renderable*>;

        Renderer(renderables_t& renderObjects, Map& map, Camera& cam);
        ~Renderer();

        // objects to be rendered
        renderables_t& renderables;

        // map
        Map& map;
        
        //camera
        Camera& camera;

        // console handle
        HANDLE hOut;

        // console size
        const COORD consoleSize{ CONSOLE_X, CONSOLE_Y };
        // CONSOLE_Y x CONSOLE_X
        char consoleScreen[CONSOLE_Y][CONSOLE_X] = {};
        std::string consoleScreenColor[CONSOLE_Y][CONSOLE_X] = {};

        CONSOLE_SCREEN_BUFFER_INFO csbi;

        // rendering options
        const int LIGHT_INTENSITY = 300;
        const float camPlaneX = 0.16f;
        const float camPlaneY = 0.09f;
        const float camZ = 0.1f;
        const float stepSize = 0.02f;
        const float yDirOffset = 0.03f;

        // brightness table
        const std::vector<std::pair<float, char>> brightnessMap {
            {900, '@'}, {800, '#'}, {700, 'b'}, {600, '0'}, {500, 'Y'}, {400, 'x'}, {300, '|'}, {200, ';'}, {100, '.'}, {0, ' '} 
        };

        // color table
        // use string_view to avoid copying
        const std::map<Map::RoomState, std::string_view> roomColorMap = {
            {Map::RoomState::wall, "\033[39m"},
            {Map::RoomState::empty, "\033[39m"},
            {Map::RoomState::start, "\033[34m"},
            {Map::RoomState::end, "\033[33m"}
        };

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

