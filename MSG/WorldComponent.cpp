#include "WorldComponent.h"
#include <Windows.h>
#include "EntityBackground.h"
#include "EntityFloorTile.h"
#include "GameManager.h"

const float WorldComponent::FPS = 60.0f;
std::vector<Lane> WorldComponent::lanes_;
Camera WorldComponent::cam_;

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

	//Initialise lanes
	lanes_ = std::vector<Lane>();
	int spacing = GAMEMANAGER.getHeight() / MAX_LANES;
	for (int i = 0; i < MAX_LANES; i++)
	{
		Lane temp = Lane(sf::Vector2f(0, i * spacing), spacing);
		lanes_.push_back(temp);
	}

	//initialise background first so that it draws first
	std::shared_ptr<EntityBackground> bg = std::make_shared<EntityBackground>();
	bg->Initialise("Assets\\Maps\\map_01.jpg", true);
	entities_.push_back(bg);

	//Initialise oil spills
	std::shared_ptr<EntityFloorTile> oil = std::make_shared<EntityFloorTile>();
	oil->Initialise("Assets\\Floor Tiles\\oil_spill.png", true, true);
	oil->setTag("oil");
	oil->setMultiplier(0.97f);
	oil->setPos(sf::Vector2f(600, 0));
	oil->setLane(2, lanes_[2]);
	entities_.push_back(oil);

	//Initialise player
	std::shared_ptr<EntityPlayer> player = std::make_shared<EntityPlayer>();
	if (!player->Initialise("Assets\\Cars\\Car.png", true))
	{
		OutputDebugString(L"Error initialising player entity\n");
		ret_val = false;
	}
	else player_ = player;//entities_.push_back(player);

	srand(time.getElapsedTime().asMilliseconds());

	int r = rand() % MAX_LANES;
	if (!ChangeLane(r, player->getPos(), player->getHeight()))
	{
		OutputDebugString(L"Error setting player lane\n");
		ret_val = false;
	}
	else
	{
		player->updatePos();
		player->setLane(r);
	}

	//initialise camera
	cam_.Initialise(player->getPos(), GAMEMANAGER.getWidth(), GAMEMANAGER.getHeight(), bg->getWidth(), bg->getHeight());
	cam_.setOffset(sf::Vector2f(-30, 0));

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
			player_->Update();

			//collision checks
			for each(auto &entity in entities_)
			{
				if (entity->isCollidable() && entity->getLane() == player_->getLane())
				{
					player_->CheckCollision(entity);
				}
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
			player_->Render(window);
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