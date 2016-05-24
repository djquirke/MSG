#pragma once
#include "MenuButtonStrip.h"
class MenuButtonStripPreview :
	public MenuButtonStrip
{
public:
	MenuButtonStripPreview() : preview_image_() {}
	~MenuButtonStripPreview() {};

	bool AddButton(Button &btn, std::string prvw_img_path, sf::Vector2f &prvw_img_pos);
	bool AddButton(const std::string &norm_path, const std::string &hover_path,
				   const sf::Vector2f &pos, bool selected, std::string dest,
				   std::string prvw_img_path, sf::Vector2f &prvw_img_pos);

private:
	sf::Sprite preview_image_;
};

