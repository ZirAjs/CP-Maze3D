#pragma once
#include <utility>
#include "GameEngine/Renderable.h"

/// <summary>
/// this is a demonstration of a class that inherits from Renderable.
/// it is a box that can be rendered in the game.
/// </summary>
class Box :
    public Engine::Renderable
{
public:
	Box(Engine::Vector postion, Engine::Vector size, float angle);
	~Box();

	bool IsPointInObject(Engine::Vector vec) const override;
	std::string GetColor() const override;

private:
	std::pair<Engine::Vector, Engine::Vector> boxCorners;
};

