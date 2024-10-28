#include "Object.h"

namespace Engine{
    Object::Object(Vector postion, Vector size, float angle, Object* parent)
    {
        transform = new Transform(postion, size, angle, (parent!=nullptr) ? parent->transform: nullptr);
    }

    Object::~Object() = default;
}