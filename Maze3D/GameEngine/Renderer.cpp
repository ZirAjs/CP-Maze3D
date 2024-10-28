#include "Renderer.h"


namespace Engine
{

    Renderer::Renderer(renderables_t& renderObj, Map& map, Camera& cam) : renderables(renderObj), map(map), camera(cam) 
    {
        InitConsole();
    }

    Renderer::~Renderer() = default;


    /// <summary>
    /// Initialize the console by setting buffer size and fetching screen information(i.e. buffer)
    /// </summary>
    void Renderer::InitConsole()
    {
        // init hOut
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        // set buffersize
        SetConsoleScreenBufferSize(hOut, consoleSize);
        GetCsbi();
    }

    /// <summary>
    /// Get Console screen buffer info
    /// </summary>
    void Renderer::GetCsbi()
    {
        if (!GetConsoleScreenBufferInfo(hOut, &csbi))
        {
            throw std::exception("Cannot fetch console info");
        }
    }

    // korean anotations are corrupted during the project due to encoding problem.
    /// <summary>
    /// Renders screen. Calculates each pixcel and Draws if changes are made.
    /// Calculations are described in the report
    /// </summary>
    void Renderer::Render()
    {
        // x,y  ߸    .  迭     [row][col]  .
        for (short y = 0; y < CONSOLE_Y; y++)
        {
            // set y as a coordinate in camera plane
            float camY = (CONSOLE_Y / 2 - y) / float(CONSOLE_Y) * camPlaneY;
            for (short x = 0; x < CONSOLE_X; x++)
            {
                // variables used for calculations
                float camAngle = camera.transform->GetWorldAngle();
                // set x as a coordinate in camera plane
                float camX = (x - CONSOLE_X / 2) / float(CONSOLE_X) * camPlaneX;

                // matrix mutiplication
                Vector dir(camZ * std::cos(camAngle) - camX * std::sin(camAngle),
                           camZ * std::sin(camAngle) + camX * std::cos(camAngle),
                           camY - yDirOffset);

                Ray r(camera.transform->GetWorldPos() + dir, Vector::Normalize(dir));

                // used to store previous point state. inorderto color the room correctly.
                Map::RoomState tempPointState = Map::empty;


                // used to store ray casted object
                const Renderable* tempObj = nullptr;

                // raycast...no possibility of 'Failed to raycast'
                // minimum iteration: (stepSize * N)^2 <100/brightness
                // 0.02^2 * N = 1/3 -> 
                for (int i = 1; i < 833; i++)
                {
                    // point to test
                    Vector test = r.pos + r.direction * stepSize * i;

                    // test result
                    // renderables test
                    Map::RoomState pointState  = Map::RoomState::empty;
					for (auto& obj : renderables)
					{
						if (obj->IsPointInObject(test))
						{
							tempObj = obj;
							pointState = Map::object;
							break;
						}
					}
                    if (pointState != Map::RoomState::object) {
                        pointState = map.IsPointInWall(test);
                    }


                    // check if ray hit the wall
                    if (0 < test.z && test.z < 1 && pointState != Map::RoomState::wall && pointState != Map::RoomState::object) {
                        tempPointState = pointState; // mark the color of the ray according to the position being.
                        continue;
                    }

					// if it hit a wall, (or an object)
                    // get the normal vector of the wall and calculate the brightness
                    Vector wallNormal;

                    if (test.z <= 0) {
                        wallNormal = Vector(0, 0, 1);
                    }
                    else if (test.z >= 1) {
                        wallNormal = Vector(0, 0, -1);
                    }
                    else if (pointState == Map::RoomState::object) {
                        wallNormal = Vector::Normalize(Vector(1, 1, 1));    // const
                        tempPointState = Map::RoomState::object;            // mark as object so that it is painted correctly.
                    }
                    else {
                        wallNormal = map.GetWallNormalVector(Ray(test, r.direction));
                    }

                    // calculate brightness
                    float brightness = std::abs(Vector::InnerProduct(r.direction, wallNormal) * LIGHT_INTENSITY / std::pow((stepSize * i), 2));

                    // match brightness
                    consoleScreen[y][x] = MatchAscii(brightness);
                    if (tempPointState != Map::object) {
                        consoleScreenColor[y][x] = roomColorMap.at(tempPointState);
                    }
                    else if (tempObj != nullptr){
						consoleScreenColor[y][x] = colorMap[tempObj->GetColor()];
                    }
                    break;
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
    void Renderer::DrawPixel(COORD coord, char value) const
    {
        SetConsoleCursorPosition(hOut, coord);
        std::cout << value << std::flush;
    }

    /// <summary>
    /// Draw 'consoleScreen' via console
    /// </summary>
    void Renderer::DrawConsoleScreen()
    {
        std::ostringstream screenStream;
        // build string
        for (int y = 0; y < CONSOLE_Y; y++)
        {
            for (int x = 0; x < CONSOLE_X; x++)
            {
                screenStream << consoleScreenColor[y][x] << consoleScreen[y][x];
            }
            screenStream << '\n';
        }

        SetConsoleCursorPosition(hOut, COORD{ 0, 0 });
        std::cout << screenStream.str() << std::flush;
    }

    /// <summary>
    /// finds the ascii character corresponding to the given brightness
    /// </summary>
    /// <param name="brightness"></param>
    /// <returns></returns>
    char Renderer::MatchAscii(float brightness)
    {

        // DBOUT("debug: " << i << std::endl)
        // DBOUT("step: "<<i<<"\n")
        // DBOUT("brightness: " << brightness << "\n")

        // FOR DEVELOPEMENT  Ÿ           Ÿ   ô .
        // brightness = (int)((stepSize * i) * 1000);

        for (const auto p : brightnessMap)
        {
            if (brightness > p.first)
            {

                // DBOUT("brightness: " << brightness << "\n")
                return p.second;
            }
        }

        // Debug
        // DBOUT("brightness: " << brightness << "\n")
        return ' ';
    }
}