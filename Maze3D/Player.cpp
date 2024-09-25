#include "Player.h"

maze::Player::Player(Vector co)
{
	pos.x = co.x;
	pos.y = co.y;
	pos.z = co.z;
}

/// <summary>
/// gets direction.
/// unit: rad
/// </summary>
/// <returns></returns>
float maze::Player::getDirection()
{
	return direction;
}

/// <summary>
/// adds direction
/// unit: rad
/// </summary>
/// <param name="angle"></param>
void maze::Player::addDirection(float angle)
{
	direction -= angle;
}

/// <summary>
/// sets direction.
/// unit: rad
/// </summary>
/// <returns></returns>
void maze::Player::setDirection(float angle)
{
	direction = -angle;
}
