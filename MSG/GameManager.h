#pragma once

#include "GameState.h"
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#define GAMEMANAGER GameManager::getInstance()

class GameManager
{
public:
	static GameManager& getInstance();
	~GameManager();

	void Initialise(int width, int height, std::string name);
	void Run();
	bool addState(const std::string &key, std::shared_ptr<GameState> state);
	void setState(const std::string &state);

	void Quit();

private:
	GameManager() {};

	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;

	std::map<std::string, std::shared_ptr<GameState>> map_states_;
	std::shared_ptr<GameState> current_state_;

	static GameManager *instance_;

	sf::RenderWindow window_;
};

