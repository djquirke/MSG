#pragma once
#include "Entity.h"
#include "EntityCar.h"
#include <memory>

class EntityPlayer :
	public Entity
{
public:
	EntityPlayer();
	~EntityPlayer();

	virtual void Update();
	virtual void Render(sf::RenderWindow &window);
	void setLane(int lane) { lane_ = lane; }
	void updatePos() { prev_pos_.y = position_.y; }
	void CheckCollision(std::shared_ptr<Entity> other);
	void setCar(EntityCar &car);

private:
	bool key_pressed_ = false;
	EntityCar car_;

	void CheckKeyboardInput();
	bool Intersects(const sf::FloatRect &other);
};