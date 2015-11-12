#include "LobbyState.h"
#include "Network.h"
#include <Windows.h>

LobbyState::~LobbyState()
{
}

bool LobbyState::Initialise()
{
	bool ret = true;
	if (!btn_start_.Initialise("Assets\\start_game_norm.bmp", "Assets\\start_game_hover.bmp",
								sf::Vector2f(200, 200)))
	{
		OutputDebugString(L"Error initialising lobby");
		ret = false;
	}
		
	return ret;
}

void LobbyState::Update()
{
	sf::Mouse mouse = sf::Mouse();
	btn_start_.Update(mouse);
}

void LobbyState::Render(sf::RenderWindow &window)
{
	btn_start_.Render(window);
}