#pragma once
#include "GameUtility.h"
#include "object.h"
 
namespace Engine
{
    class Camera : public Object
    {
    public:
        Camera(Vector position, float rotation=0.0f, Object* parent = nullptr);
        ~Camera();
    };
}

