#pragma once

#include <SFML\Graphics.hpp>

class GameState
{
public:
	GameState();
	~GameState();

	virtual bool Initialise() { return false; }
	virtual void Update() {};
	virtual void Render(sf::RenderWindow &window) {};
};

