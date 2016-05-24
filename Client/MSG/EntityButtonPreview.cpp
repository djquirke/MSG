#include "EntityButtonPreview.h"


bool EntityButtonPreview::Initialise(const std::string &sprite_path, const Button &btn,
									 const sf::Vector2f &prvw_img_pos)
{
	bool ret = true;
	btn_ = btn;

	sf::Texture temp_txtre = sf::Texture();
	if (!temp_txtre.loadFromFile(sprite_path))
	{
		ret = false;
	}

	sprite_.setTexture(temp_txtre);
	sprite_.setPosition(prvw_img_pos);

	return ret;
}