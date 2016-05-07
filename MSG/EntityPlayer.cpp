#include "EntityPlayer.h"
#include "WorldComponent.h"
#include "KeyboardHandler.h"

EntityPlayer::EntityPlayer()
{
	position_.x = 1;
}


EntityPlayer::~EntityPlayer()
{
}

void EntityPlayer::CheckKeyboardInput()
{
	//int disposition = 0;
	//position_.x++;
	engine_force_ = 0;
	braking_force_ = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		engine_force_ = move_speed_;
		braking_ = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		braking_force_ = brake_speed_;
		braking_ = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !key_pressed_)
	{
		key_pressed_ = true;
		if (WorldComponent::ChangeLane(lane_ - 1, position_, sprite_.getGlobalBounds().height))// texture_.getSize().y);
		{
			lane_ -= 1;
			prev_pos_.y = position_.y;
		}
		//lane -= 1;
		//if (lane < 0) lane = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !key_pressed_)//KEYBOARD.onKeyDown(sf::Keyboard::Down))
	{
		key_pressed_ = true;
		if (WorldComponent::ChangeLane(lane_ + 1, position_, sprite_.getGlobalBounds().height))
		{
			lane_ += 1;
			prev_pos_.y = position_.y;
		}
		//lane += 1;
		//if (lane > WorldComponent::MAX_LANES) lane = WorldComponent::MAX_LANES;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && key_pressed_)
	{
		key_pressed_ = false;
	}
}

void EntityPlayer::Update()
{
	CheckKeyboardInput();

	sf::Vector2f dir_vector = sf::Vector2f();
	dir_vector = position_ - prev_pos_; //direction vector
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
	drag.x = -0.4257 * velocity_.x * speed;
	drag.y = -0.4257 * velocity_.y * speed;

	//tyre friction
	sf::Vector2f roll_resistance = sf::Vector2f();
	roll_resistance.x = -12.8 * velocity_.x;
	roll_resistance.y = -12.8 * velocity_.y;

	//longitudinal force
	sf::Vector2f long_force = traction + drag + roll_resistance;

	sf::Vector2f acceleration = sf::Vector2f();

	if (long_force.x != 0) acceleration.x = long_force.x / 100;
	if (long_force.y != 0) acceleration.y = long_force.y / 100;

	double x = WorldComponent::delta_time;

	velocity_.x = velocity_.x + (1 / 60.0f) * acceleration.x;
	velocity_.y = velocity_.y + (1 / 60.0f) * acceleration.y;

	if (velocity_.x < 0) velocity_.x = 0;
	if (velocity_.y < 0) velocity_.y = 0;

	position_.x = position_.x + (1 / 60.0f) * velocity_.x * 5;
	position_.y = position_.y + (1 / 60.0f) * velocity_.y * 5;

	sprite_.setPosition(position_);
	WorldComponent::cam_.setCamera(position_);
}

void EntityPlayer::Render(sf::RenderWindow &window)
{
	sf::Vector2f draw_pos = sf::Vector2f();
	draw_pos.x = position_.x - WorldComponent::cam_.getPosition().x;
	draw_pos.y = position_.y - WorldComponent::cam_.getPosition().y;

	sprite_.setPosition(draw_pos);

	window.draw(sprite_);
}