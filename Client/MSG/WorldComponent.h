#pragma once
#include "GameState.h"
#include "Entity.h"
#include "EntityPlayer.h"
#include "Lane.h"
#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>
#include "Camera.h"



class WorldComponent : public GameState
{
public:
	WorldComponent();
	~WorldComponent();

	virtual bool Initialise();
	virtual void Update();
	virtual void Render(sf::RenderWindow &window);

	static bool ChangeLane(int lane, sf::Vector2f &pos, const int car_height);

	static float DeltaTime() { return 1 / FPS; }
	static const int MAX_LANES = 4;
	static Camera cam_;

private:
	std::vector<std::shared_ptr<Entity>> entities_;
	std::shared_ptr<EntityPlayer> player_;
	sf::Time last_tick_;
	sf::Clock time;
	static std::vector<Lane> lanes_;
	static const float FPS;
};

