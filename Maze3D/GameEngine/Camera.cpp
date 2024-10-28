#include "Camera.h"

namespace Engine
{
    Camera::Camera(Vector position, float rotation, Object* parent) : Object(position, Vector(0, 0, 0), rotation, parent)
    {
         
    }

    Camera::~Camera()
    {
    }
}