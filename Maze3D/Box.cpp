#include "Box.h"

Box::Box(Engine::Vector postion, Engine::Vector size, float angle) 
	: Engine::Renderable(postion, size, angle),
	boxCorners(std::make_pair(postion, postion +  Engine::Vector(0.2f,0.2f,0.2f)))
{
}

Box::~Box()
{
}

/// <summary>
/// return true if the ray is in the box
/// </summary>
/// <param name="ray"></param>
/// <returns></returns>
bool Box::IsPointInObject(Engine::Vector vec) const
{
    if (vec.x >= boxCorners.first.x && vec.x <= boxCorners.second.x &&
        vec.y >= boxCorners.first.y && vec.y <= boxCorners.second.y &&
        vec.z >= boxCorners.first.z && vec.z <= boxCorners.second.z)
    {
        return true;
    }
    return false;
}


/// <summary>
/// color of the box will be green
/// </summary>
/// <param name="ray"></param>
/// <returns></returns>
std::string Box::GetColor()  const
{
    return "green";
}
