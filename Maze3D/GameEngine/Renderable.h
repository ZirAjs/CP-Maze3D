#pragma once
#include <utility>
#include "GameUtility.h"
#include "Object.h"

namespace Engine
{
    class Renderable : public Object
    {
    public:
        Renderable()=delete;
        Renderable(Vector postion, Vector size, float angle, Object* parent = nullptr);
        ~Renderable();

        // checks if the ray is in the object
        virtual bool IsPointInObject(Vector vec)  const;
        virtual std::string GetColor() const = 0 ;
    };
}
