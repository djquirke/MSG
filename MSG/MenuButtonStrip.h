#pragma once

#include "Button.h"
#include <vector>

class MenuButtonStrip
{
public:
	MenuButtonStrip();
	~MenuButtonStrip();

	void AddButton(const Button &btn);
	void AddButton(const std::string &norm_path, const std::string &hover_path,
				   const sf::Vector2f &pos);
	void Update();
	void Render(sf::RenderWindow &window);

private:
	std::vector<Button> vec_btn_;
};

