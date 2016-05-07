#pragma once
#include "Entity.h"
class EntityCar :
	public Entity
{
public:
	EntityCar();
	~EntityCar();

	int getCarHeight() { return sprite_.getGlobalBounds().height; }

protected:
	float move_speed_ = 5000;
	float brake_speed_ = 7000;
	sf::Vector2f velocity_;
	float engine_force_ = 0;
	float braking_force_ = 0;
	bool braking_ = false;
	int lane_ = 0;
};

