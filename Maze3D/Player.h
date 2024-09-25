#pragma once
#include "Map.h"
#include "GameMath.h"

namespace maze {

	class Player
	{

		public:
			Player(Vector);

			//player position
			Vector pos;
			float getDirection();
			void addDirection(float angle);
			void setDirection(float angle);

			// preference
			float rotationFactor = 0.05f * Pi;
			float speedFactor = 0.3f;

	private:
		float direction = 0.0f;

	};

}

