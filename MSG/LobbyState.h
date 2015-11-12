#pragma once

#include "GameState.h"
#include "Button.h"
#include <SFML\Graphics.hpp>

class LobbyState : public GameState
{
public:
	LobbyState() : btn_start_() {};
	~LobbyState();

	virtual bool Initialise();
	virtual void Update();
	virtual void Render(sf::RenderWindow &window);

private:
	Button btn_start_;
};

