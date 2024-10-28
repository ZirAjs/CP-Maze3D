#include "GameUtility.h"

namespace Engine
{

    /// <summary>
    /// initialize as zero vector
    /// </summary>
    Vector::Vector() : x(0), y(0), z(0) {}

    /// <summary> 
    /// initialize vector with given componenets
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    Vector::Vector(const float x, const float y, const float z) : x(x), y(y), z(z) {}

    /// <summary>
    /// returns size of vector(this)
    /// </summary>
    /// <returns></returns>
    float Vector::Size() const
    {
        return std::sqrtf(std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2));
    }

#pragma region BasicOperators


    Vector& Vector::operator=(const Vector& a)
    {
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }

    Vector& Vector::operator+=(const Vector& a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    Vector& Vector::operator-=(const Vector& a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    Vector Vector::operator+(const Vector& a) const
    {
        return Vector(a.x + x, a.y + y, a.z + z);
    }

    Vector Vector::operator-(const Vector& a) const
    {
        return {x - a.x, y - a.y, z - a.z};
    }

    Vector Vector::operator/(const float a) const
    {
        return {x / a, y / a, z / a};
    }

    Vector Vector::operator*(const float a) const
    {
        return {x * a, y * a, z * a};
    }

#pragma endregion

    /// <summary>
    /// return Normalize form of given vector
    /// </summary>
    /// <param name="a"></param>
    /// <returns></returns>
    Vector Vector::Normalize(const Vector& a)
    {
        return a / a.Size();
    }

    /// <summary>
    /// calculate innerproduct of two vector
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    float Vector::InnerProduct(const Vector& a, const  Vector& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    /// <summary>
    /// generates zero vector
    /// </summary>
    /// <returns></returns>
    const Vector Vector::Zero()
    {
        return Vector(0, 0, 0);
    }


    Ray::Ray(const Vector& pos, const Vector& dir)
    {
        this->pos = pos;
        this->direction = dir;
    }

    Light::Light(const std::string& col, const Vector& dir) : color(col), direction(dir)
    {
    }

    

}
