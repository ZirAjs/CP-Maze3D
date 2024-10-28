#include "Transform.h"

namespace Engine
{
	Transform::Transform(Vector postion, Vector size, float angle, Transform* p) : localPos(postion), size(size), localAngle(angle), parent(p)
	{
	}

	/// <summary>
	/// need to implement destruction of child transforms
	/// </summary>
	Transform::~Transform()
	{
	}

	/// <summary>
	/// set the position of the object
	/// </summary>
	/// <param name="pos"></param>
	void Transform::SetPosition(Vector pos)
	{
		localPos = pos;
	}

	/// <summary>
	/// set the angle of the object
	/// </summary>
	/// <param name="angle"></param>
	void Transform::SetAngle(float angle)
	{
		localAngle = angle;
	}

	/// <summary>
	/// add vector to the object position
	/// </summary>
	/// <param name="add_pos"></param>
	void Transform::AddPosition(Vector add_pos)
	{
		localPos = add_pos + localPos;
	}

	/// <summary>
	/// add an angle to the object
	/// </summary>
	/// <param name="delta_angle"></param>
	void Transform::AddAngle(float delta_angle)
	{
		localAngle += delta_angle;
	}

	/// <summary>
	/// get the world position of the object
	/// </summary>
	/// <returns></returns>
	Vector Transform::GetWorldPos() const
	{
		if (parent != nullptr)
		{
			return parent->GetWorldPos() + localPos;
		}
		else
		{
			return localPos;
		}
	}

	/// <summary>
	/// get the local position of the object
	/// </summary>
	/// <returns></returns>
	Vector Transform::GetLocalPos() const
	{
		return localPos;
	}

	/// <summary>
	/// get the world angle of the object
	/// </summary>
	/// <returns></returns>
	float Transform::GetWorldAngle() const
	{
		if (parent != nullptr)
		{
			return parent->GetWorldAngle() + localAngle;
		}
		else
		{
			return localAngle;
		}
	}

	/// <summary>
	/// get the local angle of the object
	/// </summary>
	/// <returns></returns>
	float Transform::GetLocalAngle() const
	{
		return localAngle;
	}

	/// <summary>
	/// get the size of the object
	/// </summary>
	/// <returns></returns>
	Vector Transform::GetSize() const
	{
		return size;
	}
}