#pragma once

#include "GameState.h"
#include "MenuButtonStrip.h"
#include <SFML\Graphics.hpp>

class LobbyState : public GameState
{
public:
	LobbyState() : btns_() {};
	~LobbyState();

	virtual bool Initialise();
	virtual void Update();
	virtual void Render(sf::RenderWindow &window);

private:
	MenuButtonStrip btns_;
};

