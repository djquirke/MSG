#include "KeyboardHandler.h"

KeyboardHandler* KeyboardHandler::instance_ = nullptr;

KeyboardHandler& KeyboardHandler::getInstance()
{
	if (instance_ == nullptr)
		instance_ = new KeyboardHandler();

	return *instance_;
}

KeyboardHandler::~KeyboardHandler()
{
}

bool KeyboardHandler::onKeyDown(const sf::Keyboard::Key &key)
{
	bool ret = false;

	if (sf::Keyboard::isKeyPressed(key) && !key_pressed_)
	{
		key_pressed_ = true;
		ret = true;
		current_key_ = key;
	}
	else if (!sf::Keyboard::isKeyPressed(key) && key_pressed_ && (current_key_ == key))
	{
		key_pressed_ = false;
		ret = false;
	}

	return ret;
}

bool KeyboardHandler::onKeyHold(const sf::Keyboard::Key &key)
{
	return sf::Keyboard::isKeyPressed(key);
}