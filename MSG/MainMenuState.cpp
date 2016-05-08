#include "MainMenuState.h"
#include "Network.h"
#include <Windows.h>

MainMenuState::~MainMenuState()
{
}

bool MainMenuState::Initialise()
{
	bool ret = true;

	btns_ = MenuButtonStrip();
	btns_.Initialise(Alignment::VERTICAL);

	int x_align = 325;

	if (!btns_.AddButton("Assets\\Buttons\\join_game_norm.bmp", "Assets\\Buttons\\join_game_hover.bmp",
		sf::Vector2f(x_align, 75), true, "game"))
	{
		ret = false;
	}

	if (!btns_.AddButton("Assets\\Buttons\\settings_norm.bmp", "Assets\\Buttons\\settings_hover.bmp",
		sf::Vector2f(x_align, 200), false, "settings"))
	{
		ret = false;
	}

	if (!btns_.AddButton("Assets\\Buttons\\shop_norm.bmp", "Assets\\Buttons\\shop_hover.bmp",
		sf::Vector2f(x_align, 325), false, "shop"))
	{
		ret = false;
	}


	if (!btns_.AddButton("Assets\\Buttons\\quit_norm.bmp", "Assets\\Buttons\\quit_hover.bmp",
		sf::Vector2f(x_align, 450), false, "quit"))
	{
		ret = false;
	}
		
	return ret;
}

void MainMenuState::Update()
{
	btns_.Update();
}

void MainMenuState::Render(sf::RenderWindow &window)
{
	btns_.Render(window);
}