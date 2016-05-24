#include "EntityPlayer.h"
#include "EntityFloorTile.h"
#include "WorldComponent.h"
#include "KeyboardHandler.h"

EntityPlayer::EntityPlayer()
{
	position_.x = 1;
	car_ = EntityCar();
}


EntityPlayer::~EntityPlayer()
{
}

void EntityPlayer::CheckKeyboardInput()
{
	car_.resetForces();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		car_.Accelerate();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		car_.Brake();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !key_pressed_)
	{
		key_pressed_ = true;
		if (WorldComponent::ChangeLane(lane_ - 1, position_, sprite_.getGlobalBounds().height))// texture_.getSize().y);
		{
			lane_ -= 1;
			prev_pos_.y = position_.y;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !key_pressed_)//KEYBOARD.onKeyDown(sf::Keyboard::Down))
	{
		key_pressed_ = true;
		if (WorldComponent::ChangeLane(lane_ + 1, position_, sprite_.getGlobalBounds().height))
		{
			lane_ += 1;
			prev_pos_.y = position_.y;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && key_pressed_)
	{
		key_pressed_ = false;
	}
}

void EntityPlayer::Update()
{
	CheckKeyboardInput();

	car_.UpdateForces(position_, prev_pos_);

	sf::Vector2f velocity = car_.getVelocity();

	position_.x = position_.x + WorldComponent::DeltaTime() * velocity.x *5;
	position_.y = position_.y + WorldComponent::DeltaTime() * velocity.y *5;

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

void EntityPlayer::CheckCollision(std::shared_ptr<Entity> other)
{
	bool collided = false;
	if (Intersects(other->getRect()))//.intersects(other->getRect(), getRect()))
	{
		//collide with oil or speed tile
		if (other->getTag() == "oil" || other->getTag() == "speed_boost")
		{
			collided = true;
			std::shared_ptr<EntityFloorTile> temp = std::static_pointer_cast<EntityFloorTile>(other);
			car_.setMultiplier(temp->getMultiplier());
		}
	}

	if (!collided)
	{
		car_.setMultiplier(1);
	}
}

bool EntityPlayer::Intersects(const sf::FloatRect &other)
{
	sf::FloatRect player_rect = getRect();
	return (player_rect.left <= other.width &&
		player_rect.width >= other.left &&
		player_rect.top <= other.height &&
		player_rect.height >= other.top);
}

void EntityPlayer::setCar(EntityCar &car)
{
	car_ = car;
	sprite_.setTexture(*car.getTexture());
}