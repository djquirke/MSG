#pragma once
#include "GameState.h"
class LobbyState :
	public GameState
{
public:
	LobbyState();
	~LobbyState();

	bool Initialise();
	void Update();
	void Render(sf::RenderWindow &window);

private:

};

