#include "LobbyState.h"
#include "Network.h"
#include <Windows.h>

LobbyState::~LobbyState()
{
}

bool LobbyState::Initialise()
{
	bool ret = true;

	btns_ = MenuButtonStrip();
	btns_.Initialise(Alignment::VERTICAL);

	if (!btns_.AddButton("Assets\\start_game_norm.bmp", "Assets\\start_game_hover.bmp",
		sf::Vector2f(200, 200), true))
	{
		ret = false;
	}

	if (!btns_.AddButton("Assets\\start_game_norm.bmp", "Assets\\start_game_hover.bmp",
		sf::Vector2f(200, 300), false))
	{
		ret = false;
	}

		
	return ret;
}

void LobbyState::Update()
{
	btns_.Update();
}

void LobbyState::Render(sf::RenderWindow &window)
{
	btns_.Render(window);
}