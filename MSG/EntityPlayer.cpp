#include "EntityPlayer.h"


EntityPlayer::EntityPlayer() : move_speed_(3)
{
}


EntityPlayer::~EntityPlayer()
{
}

void EntityPlayer::Update()
{
	//position_.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		position_.x -= move_speed_;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		position_.x += move_speed_;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position_.y -= move_speed_;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		position_.y += move_speed_;
	}
	sprite_.setPosition(position_);
}
