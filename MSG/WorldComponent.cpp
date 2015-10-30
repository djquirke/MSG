#include "WorldComponent.h"
#include <Windows.h>
#include "EntityPlayer.h"

WorldComponent::WorldComponent() : entities_(NULL), time()
{
}


WorldComponent::~WorldComponent()
{
}

bool WorldComponent::Initialise()
{
	bool ret_val = true;
	last_tick_ = time.getElapsedTime();

	std::shared_ptr<EntityPlayer> new_entity = std::make_shared<EntityPlayer>();
	if (!new_entity->Initialise("Assets\\tile_map.bmp", true))
	{
		OutputDebugString(L"Error initialising entity\n");
		ret_val = false;
	}
	else
	{
		entities_.push_back(new_entity);
	}

	return ret_val;
}

void WorldComponent::Update()
{
	//logic loop
	sf::Time elapsed = time.getElapsedTime();
	if ((elapsed - last_tick_).asMilliseconds() > (1000 / FPS))
	{
		last_tick_ = elapsed;
		for each (auto &entity in entities_)
		{
			entity->Update();
		}
	}
}

void WorldComponent::Render(sf::RenderWindow &window)
{
	//loop through all entities and draw them if they are alive
	for each (auto &entity in entities_)
	{
		if (entity->isAlive())
		{
			entity->Render(window);
		}
	}
}