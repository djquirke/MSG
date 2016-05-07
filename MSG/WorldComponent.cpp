#include "WorldComponent.h"
#include <Windows.h>
#include "EntityPlayer.h"
#include "GameManager.h"

const float WorldComponent::FPS = 60.0f;
const float WorldComponent::delta_time = 1 / FPS;
std::vector<Lane> WorldComponent::lanes_;

WorldComponent::WorldComponent() : entities_(NULL), time()//, lanes_()
{
}

WorldComponent::~WorldComponent()
{
}

bool WorldComponent::Initialise()
{
	bool ret_val = true;
	last_tick_ = time.getElapsedTime();

	std::shared_ptr<EntityPlayer> player = std::make_shared<EntityPlayer>();
	if (!player->Initialise("Assets\\tile_map.bmp", true))
	{
		OutputDebugString(L"Error initialising player entity\n");
		ret_val = false;
	}
	else
	{
		entities_.push_back(player);
	}

	//Initialise lanes
	lanes_ = std::vector<Lane>();
	int spacing = GAMEMANAGER.getHeight() / MAX_LANES;
	for (int i = 0; i < MAX_LANES; i++)
	{
		Lane temp = Lane(sf::Vector2f(0, i * spacing), spacing);
		lanes_.push_back(temp);
	}

	srand(time.getElapsedTime().asMilliseconds());

	int r = rand() % MAX_LANES;
	if (!ChangeLane(r, player->getPos(), player->getCarHeight()))
	{
		OutputDebugString(L"Error setting player lane\n");
		ret_val = false;
	}
	//sf::Vector2f player_start_pos = lanes_[r].
	//new_entity->setLane(r, )

	return ret_val;
}

void WorldComponent::Update()
{
	if (running)
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
}

void WorldComponent::Render(sf::RenderWindow &window)
{
	if (running)
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
}

bool WorldComponent::ChangeLane(int lane, sf::Vector2f &pos, int car_height)
{
	if (lane < 0) return false;
	if (lane >= MAX_LANES) return false;

	//calculate offset within lane
	pos.y = ((lanes_[lane].width - car_height) / 2) + lanes_[lane].pos.y;
	return true;
}