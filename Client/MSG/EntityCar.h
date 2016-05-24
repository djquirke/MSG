#pragma once
#include "Entity.h"
class EntityCar :
	public Entity
{
public:
	EntityCar();
	~EntityCar();

	void EntityCar::InitialiseCarValues(const std::string &sprite_path, float torque, float brake_speed, float mass);
	//calculates the new velocity
	void Accelerate();
	void Brake();
	void resetForces() { engine_force_ = 0; braking_force_ = 0; }
	sf::Vector2f getVelocity() { return velocity_; }
	void UpdateForces(const sf::Vector2f &pos, const sf::Vector2f &prev_pos);
	void setMultiplier(float val) { speed_multiplier_ = val; }

protected:
	float torque_ = 5000;
	float brake_speed_ = 10000;
	float mass_ = 300;

private:
	sf::Vector2f velocity_;
	float engine_force_ = 0;
	float braking_force_ = 0;
	bool braking_ = false;
	float speed_multiplier_ = 1;
};

