#include "GameManager.h"
#include "LobbyState.h"
#include "WorldComponent.h"


GameManager* GameManager::instance_ = NULL;

GameManager& GameManager::getInstance()
{
	if (instance_ == NULL)
		instance_ = new GameManager();

	return *instance_;
}

GameManager::~GameManager()
{
}

void GameManager::Initialise()
{
	map_states_ = std::map<std::string, std::shared_ptr<GameState>>();
	active_state_ = std::string();
}

void GameManager::Run(sf::RenderWindow &window)
{
	std::shared_ptr<GameState> current_state = map_states_[active_state_];
	current_state->Update();
	current_state->Render(window);
}

bool GameManager::addState(const std::string &key, std::shared_ptr<GameState> state)
{
	bool ret = true;

	if (state->Initialise())
		map_states_.insert(std::make_pair(key, state));
	else
		ret = false;

	return ret;
}

void GameManager::setState(const std::string &state)
{
	active_state_ = state;
}