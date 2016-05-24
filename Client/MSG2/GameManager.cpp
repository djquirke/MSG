#include "GameManager.h"
#include "MainMenuState.h"
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

void GameManager::Initialise(int width, int height, std::string name)
{
	window_.create(sf::VideoMode(width, height), name);

	map_states_ = std::map<std::string, std::shared_ptr<GameState>>();
	current_state_ = std::make_shared<GameState>();
}

void GameManager::Run()
{
	while (window_.isOpen())
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_.close();
			}
		}

		window_.clear();
		current_state_->Update();
		current_state_->Render(window_);

		window_.display();
	}
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
	current_state_->setRunning(false);
	current_state_ = map_states_[state];
	current_state_->setRunning(true);
}

void GameManager::Quit()
{
	window_.close();
}