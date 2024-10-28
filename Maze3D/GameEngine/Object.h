#pragma once
#include "GameUtility.h"
#include "Transform.h"
#include <memory>

namespace Engine
{
    class Object {


    public:
        Object() = delete;
        Object(Vector postion, Vector size, float angle, Object* parent=nullptr);
        ~Object();

        Transform* transform;
    };
}

