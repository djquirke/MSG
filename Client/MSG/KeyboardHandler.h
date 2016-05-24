#pragma once

#include <SFML\Window\Keyboard.hpp>

#define KEYBOARD KeyboardHandler::getInstance()

class KeyboardHandler
{
public:
	static KeyboardHandler& getInstance();
	~KeyboardHandler();

	//runs only once when key is first pressed
	bool onKeyDown(const sf::Keyboard::Key &key);
	//runs whilst key held down
	bool onKeyHold(const sf::Keyboard::Key &key);

private:

	KeyboardHandler() : key_pressed_(false) {};

	KeyboardHandler(KeyboardHandler const&) = delete;
	void operator=(KeyboardHandler const&) = delete;

	static KeyboardHandler *instance_;
	bool key_pressed_;
	sf::Keyboard::Key current_key_;
};

