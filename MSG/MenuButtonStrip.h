#pragma once

#include "Button.h"
#include <vector>

enum Alignment
{
	HORIZONTAL,
	VERTICAL
};

class MenuButtonStrip
{
public:
	MenuButtonStrip() : vec_btn_(NULL), next_key_pressed_(false), prev_key_pressed_(false) {};
	~MenuButtonStrip();

	void Initialise(Alignment direction);

	void AddButton(Button &btn);
	bool AddButton(const std::string &norm_path, const std::string &hover_path,
				   const sf::Vector2f &pos, bool selected);
	void Update();
	void Render(sf::RenderWindow &window);

private:
	std::vector<Button> vec_btn_;
	Alignment direction_;
	bool next_key_pressed_;
	bool prev_key_pressed_;

	sf::Keyboard::Key next_key_;
	sf::Keyboard::Key prev_key_;

	void checkKeyboardInput();
};

