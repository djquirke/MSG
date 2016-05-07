#pragma once
#include "EntityCar.h"

class EntityPlayer :
	public EntityCar
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

	void CheckKeyboardInput();
};