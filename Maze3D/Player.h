#pragma once
#include "GameEngine/Map.h"
#include "GameEngine/GameUtility.h"
#include "GameEngine/Object.h"

namespace maze {

    class Player : public Engine::Object
    {

        public:
            Player(Engine::Vector position, float angle = 0, Object* parent = nullptr) ;
            ~Player();

            // preference
            float rotationFactor = 0.05f * Engine::Pi;
            float speedFactor = 0.3f;

    private:
        float direction = 0.0f;

    };

}

