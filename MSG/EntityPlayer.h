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
	void setLane(int lane, sf::Vector2f &start_pos) { lane_ = lane; position_ = start_pos; }

private:
	bool key_pressed_ = false;

	void CheckKeyboardInput();

	//DEBUG STUFF
	//sf::Vertex line[];
};