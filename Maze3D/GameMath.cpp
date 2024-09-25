#include "GameMath.h"

namespace maze {

	/// <summary>
	/// initialize as zero vector
	/// </summary>
	Vector::Vector()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	/// <summary>
	/// initialize vector with given componenets
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector::Vector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/// <summary>
	/// returns size of vector(this)
	/// </summary>
	/// <returns></returns>
	float Vector::Size() const
	{
		return std::sqrtf(std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2));
	}

	Vector Vector::operator=(Vector a) {
		x = a.x;
		y = a.y;
		z = a.z;
		return a;
	}

	Vector Vector::operator+=(Vector a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return a;
	}

	Vector Vector::operator-=(Vector a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return a;
	}

	Vector Vector::operator+(Vector a) {
		return { a.x + x,a.y + y , a.z + z };
	}

	Vector Vector::operator-(Vector a) {
		return { x - a.x , y - a.y , z - a.z };
	}

	Vector Vector::operator/(float a) {
		return { x / a , y / a , z / a };
	}

	Vector Vector::operator*(float a)
	{
		return { x * a , y * a , z * a };
	}

	/// <summary>
	/// static function for vector.size
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	float Vector::Size(Vector a) {
		return std::sqrtf(std::powf(a.x, 2) + std::powf(a.y, 2) + std::powf(a.z, 2));
	}

	/// <summary>
	/// return Normalize form of given vector
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	Vector Vector::Normalize(Vector a)
	{
		return a/a.Size();
	}

	
	/// <summary>
	/// calculate innerproduct of two vector
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	float Vector::InnerProduct(Vector a, Vector b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/// <summary>
	/// generates zero vector
	/// </summary>
	/// <returns></returns>
	const Vector Vector::Zero()
	{
		return Vector(0,0,0);
	}

	Ray::Ray(Vector pos, Vector dir)
	{
		this->pos = pos;
		this->direction = dir;
	}

}

