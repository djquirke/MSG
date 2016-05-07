#pragma once
#include "GameState.h"
#include "Entity.h"
#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

struct Lane
{
public:
	sf::Vector2f pos;
	int width;

	Lane(sf::Vector2f position, int w)
	{
		pos = position;
		width = w;
	}
};

class WorldComponent : public GameState
{
public:
	WorldComponent();
	~WorldComponent();

	virtual bool Initialise();
	virtual void Update();
	virtual void Render(sf::RenderWindow &window);

	static bool ChangeLane(int lane, sf::Vector2f &pos, const int car_height);

	static const float FPS;// = 60.0f;
	static const float delta_time;// = 1 / FPS;//DeltaTime() { return delta_time; }
	static const int MAX_LANES = 4;
	
private:
	std::vector<std::shared_ptr<Entity>> entities_;
	sf::Time last_tick_;
	sf::Clock time;
	static std::vector<Lane> lanes_;
	//const float FPS = 60.0f;
	//const float delta_time = 1 / FPS;
};

