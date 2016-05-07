#include "Entity.h"
#include <Windows.h>
#include "WorldComponent.h"

Entity::Entity() : sprite_(), position_(), texture_(), isAlive_(false), prev_pos_()
{
}


Entity::~Entity()
{
}

bool Entity::Initialise(const std::string &sprite_path, bool alive)
{
	bool ret_val = true;
	isAlive_ = alive;

	if (!texture_.loadFromFile(sprite_path))
	{
		OutputDebugString(L"Error loading file\n");
		ret_val = false;
	}
	
	sprite_.setTexture(texture_);

	return ret_val;
}

void Entity::Render(sf::RenderWindow &window)
{
	sf::Vector2f draw_pos = sf::Vector2f();
	draw_pos.x = position_.x - WorldComponent::cam_.getPosition().x;
	draw_pos.y = position_.y - WorldComponent::cam_.getPosition().y;

	sprite_.setPosition(draw_pos);

	window.draw(sprite_);
}

void Entity::Update()
{

}

void Entity::Destroy()
{

}