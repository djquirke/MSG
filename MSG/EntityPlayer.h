#pragma once
#include "Entity.h"
#include "EntityCar.h"

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

private:
	bool key_pressed_ = false;
	EntityCar car_;
	int lane_ = 0;

	void CheckKeyboardInput();
};