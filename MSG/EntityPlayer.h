#pragma once
#include "Entity.h"
class EntityPlayer :
	public Entity
{
public:
	EntityPlayer();
	~EntityPlayer();

	virtual void Update();

private:
	float move_speed_;
};