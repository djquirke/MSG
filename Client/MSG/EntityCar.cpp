#include "EntityCar.h"
#include "WorldComponent.h"


EntityCar::EntityCar()
{
}


EntityCar::~EntityCar()
{
}

void EntityCar::Accelerate()
{
	braking_ = false;
	engine_force_ = torque_;
	//UpdateForces(pos, prev_pos);
}

void EntityCar::Brake()
{
	braking_ = true;
	braking_force_ = brake_speed_;
	//UpdateForces(pos, prev_pos);
}

void EntityCar::UpdateForces(const sf::Vector2f &pos, const sf::Vector2f &prev_pos)
{
	sf::Vector2f dir_vector = sf::Vector2f();
	dir_vector = pos - prev_pos;
	double dir_magnitude = sqrt((dir_vector.x * dir_vector.x) + (dir_vector.y * dir_vector.y));

	sf::Vector2f traction = sf::Vector2f();

	if (dir_magnitude != 0)
	{
		sf::Vector2f dir_unit_vector = sf::Vector2f(dir_vector.x / dir_magnitude, dir_vector.y / dir_magnitude);

		if (braking_)
		{
			traction = -sf::Vector2f(dir_unit_vector.x * braking_force_, dir_unit_vector.y * braking_force_);
		}
		else
		{
			traction = sf::Vector2f(dir_unit_vector.x * engine_force_, dir_unit_vector.y * engine_force_);
		}
	}

	double speed = sqrt((velocity_.x * velocity_.x) + (velocity_.y * velocity_.y));

	//air resistance
	sf::Vector2f drag = sf::Vector2f();
	drag.x = -0.4257 * velocity_.x * speed; //0.4257
	drag.y = -0.4257 * velocity_.y * speed;

	//tyre friction
	sf::Vector2f roll_resistance = sf::Vector2f();
	roll_resistance.x = -12.8 * velocity_.x; //12.8
	roll_resistance.y = -12.8 * velocity_.y;

	//longitudinal force
	sf::Vector2f long_force = traction + drag + roll_resistance;

	sf::Vector2f acceleration = sf::Vector2f();

	if (long_force.x != 0) acceleration.x = long_force.x / mass_;
	if (long_force.y != 0) acceleration.y = long_force.y / mass_;

	velocity_.x = velocity_.x * speed_multiplier_ + WorldComponent::DeltaTime() * acceleration.x;
	velocity_.y = velocity_.y * speed_multiplier_ + WorldComponent::DeltaTime() * acceleration.y;
	if (speed_multiplier_ < 1)
	{
		int x = 5;
	}

	if (velocity_.x < 0) velocity_.x = 0;
	if (velocity_.y < 0) velocity_.y = 0;
}

void EntityCar::InitialiseCarValues(const std::string &sprite_path, float torque, float brake_speed, float mass)
{
	torque_ = torque;
	brake_speed_ = brake_speed;
	mass_ = mass;

	texture_.loadFromFile(sprite_path);
	sprite_.setTexture(texture_);
}