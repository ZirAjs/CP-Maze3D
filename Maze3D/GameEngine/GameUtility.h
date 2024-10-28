#pragma once

#include <cmath>
#include <string>
#include <map>

namespace Engine {

	const float Pi = 3.14159265359f;

	// color table
	// use string_view to avoid copying
	using colorTable_t = std::map<std::string_view, std::string_view>;
	static colorTable_t colorMap = {
		{"black", "\033[30m"},
		{"red", "\033[31m"},
		{"green", "\033[32m"},
		{"yellow", "\033[33m"},
		{"blue", "\033[34m"},
		{"magenta", "\033[35m"},
		{"cyan", "\033[36m"},
		{"white", "\033[37m"},
	};

	/// <summary>
	/// 3D vector with three component
	/// </summary>
	struct Vector {
		float x;
		float y;
		float z;

		Vector();
		Vector(const float x, const float y, const float z);

		float Size() const;

		// operator overloading

		Vector& operator=(const Vector&);

		Vector& operator+=(const Vector&);

		Vector& operator-=(const Vector&);

		Vector operator+(const Vector&) const;

		Vector operator-(const Vector&) const;

		Vector operator/(const float) const;

		Vector operator*(const float) const;

		static Vector Normalize(const Vector&);

		static float InnerProduct(const Vector& a, const Vector& b);

		static const Vector Zero();
	};

	/// <summary>
	/// Ray. Stores position and direction
	/// </summary>
	struct Ray
	{
		Vector pos;
		Vector direction;

		Ray() = delete;
		Ray(const Vector& pos, const Vector& dir);
	};

	/// <summary>
	/// Property of light.
	/// Contains brightness and color
	/// </summary>
	struct Light{
		std::string color;
		Vector direction;

		Light() = delete;
		Light(const std::string& color, const Vector& direction);
	};
}
