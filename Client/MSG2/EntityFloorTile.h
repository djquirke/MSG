#pragma once
#include "Entity.h"
class EntityFloorTile :
	public Entity
{
public:
	EntityFloorTile();
	~EntityFloorTile();

	void setMultiplier(float val) { speed_multiplier_ = val; }
	float getMultiplier() { return speed_multiplier_; }

private:
	float speed_multiplier_ = 0;
};

