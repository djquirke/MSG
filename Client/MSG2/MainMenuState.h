#pragma once

#include "GameState.h"
#include "MenuButtonStrip.h"
#include <SFML\Graphics.hpp>

class MainMenuState : public GameState
{
public:
	MainMenuState() : btns_() {};
	~MainMenuState();

	virtual bool Initialise();
	virtual void Update();
	virtual void Render(sf::RenderWindow &window);

private:
	MenuButtonStrip btns_;
};

