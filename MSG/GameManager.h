#pragma once

#include "GameState.h"
#include <map>
#include <memory>

#define GAMEMANAGER GameManager::getInstance()

class GameManager
{
public:
	static GameManager& getInstance();
	~GameManager();

	void Initialise();
	void Run(sf::RenderWindow &window);
	bool addState(const std::string &key, std::shared_ptr<GameState> state);
	void setState(const std::string &state);

private:
	GameManager() {};

	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;

	std::map<std::string, std::shared_ptr<GameState>> map_states_;
	std::string active_state_;

	static GameManager *instance_;
};

