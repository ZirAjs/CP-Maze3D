#pragma once
#include "GameUtility.h"

namespace Engine
{
    class Transform 
    {
    public:
        Transform(Vector postion, Vector size, float angle, Transform* p = nullptr);
        ~Transform();

        // parent transform
        Transform* parent;

        void SetPosition(Vector pos);
        void SetAngle(float angle);


        void AddPosition(Vector add_pos);
        void AddAngle(float delta_angle);

        Vector GetWorldPos() const;
        Vector GetLocalPos() const;
            
        float GetWorldAngle() const;
        float GetLocalAngle() const;

        Vector GetSize() const;

    private:
        Vector localPos;
        Vector size;
        float localAngle;
    };
}

