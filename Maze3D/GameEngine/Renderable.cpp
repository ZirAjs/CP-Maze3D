#include "Renderable.h"

namespace Engine	
{
    Renderable::Renderable(Vector postion, Vector size, float angle, Object* parent) : Object(postion, size, angle, parent)
    {
    }

    Renderable::~Renderable() = default;

    bool Renderable::IsPointInObject(Vector vec) const
    {
        return false;
    }


}