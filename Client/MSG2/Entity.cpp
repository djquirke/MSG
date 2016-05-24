#include "Entity.h"
#include <Windows.h>
#include "WorldComponent.h"

Entity::Entity() : sprite_(), position_(), texture_(), isAlive_(false), prev_pos_()
{
}


Entity::~Entity()
{
}

bool Entity::Initialise(const std::string &sprite_path, bool alive, bool collidable)
{
	bool ret_val = true;
	isAlive_ = alive;
	isCollidable_ = collidable;

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

void Entity::setLane(int num, const Lane &lane)
{
	position_.y = ((lane.width - sprite_.getGlobalBounds().height) / 2) + lane.pos.y;
	prev_pos_.y = position_.y;
	lane_ = num;
}

sf::FloatRect Entity::getRect()
{
	sf::FloatRect ret = sf::FloatRect();
	ret.left = position_.x;
	ret.top = position_.y;
	ret.width = position_.x + getWidth();
	ret.height = position_.y + getHeight();
	//ret.left = sprite_.getGlobalBounds().left;
	//ret.top = sprite_.getGlobalBounds().top;
	//ret.width = sprite_.getGlobalBounds().left + sprite_.getGlobalBounds().width;
	//ret.height = sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().height;

	return ret;
}