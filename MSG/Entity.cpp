#include "Entity.h"
#include <Windows.h>

Entity::Entity() : sprite_(), position_(), texture_(), isAlive_(false)
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
	window.draw(sprite_);
}

void Entity::Update()
{

}

void Entity::Destroy()
{

}