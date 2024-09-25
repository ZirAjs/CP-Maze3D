#pragma once

#include <cmath>

namespace maze {

	const float Pi = 3.14159265359f;

	/// <summary>
	/// 3D vector with three component
	/// </summary>
	struct Vector {
		float x;
		float y;
		float z;

		Vector();
		Vector(float x, float y, float z);

	public:

		float Size() const;

		// operator overloading

		Vector operator=(Vector);

		Vector operator+=(Vector);

		Vector operator-=(Vector);

		Vector operator+(Vector);

		Vector operator-(Vector);

		Vector operator/(float);

		Vector operator*(float);

		static Vector Normalize(Vector);

		static float InnerProduct(Vector a, Vector b);

		static const Vector Zero();

		static float Size(Vector);
	};

	/// <summary>
	/// Ray. Stores position and direction
	/// </summary>
	struct Ray
	{
		Vector pos;
		Vector direction;

		Ray(Vector pos, Vector dir);
	};

}
