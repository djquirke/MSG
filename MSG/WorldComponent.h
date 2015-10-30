#pragma once
#include "Entity.h"
#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

class WorldComponent
{
public:
	WorldComponent();
	~WorldComponent();

	bool Initialise();
	void Update();
	void Render(sf::RenderWindow &window);

private:
	std::vector<std::shared_ptr<Entity>> entities_;
	sf::Time last_tick_;
	sf::Clock time;
	float FPS = 60.0f;
};

