#include "Button.h"
#include <Windows.h>

Button::~Button()
{
}

bool Button::Initialise(const std::string &norm_path, const std::string &hover_path,
						const sf::Vector2f &pos)
{
	bool ret = true;

	norm_texture_ = sf::Texture();
	if (!norm_texture_.loadFromFile(norm_path))
	{
		OutputDebugString(L"Error loading button texture");
		ret = false;
	}
	
	hover_texture_ = sf::Texture();
	if (!hover_texture_.loadFromFile(hover_path))
	{
		OutputDebugString(L"Error loading button texture");
		ret = false;
	}

	sprite_.setTexture(norm_texture_);
	sprite_.setPosition(pos);

	return ret;
}

void Button::Update(const sf::RenderWindow &window)
{
	if (hasCollided(window))
		sprite_.setTexture(hover_texture_);
	else
		sprite_.setTexture(norm_texture_);
}

bool Button::hasCollided(const sf::RenderWindow &window)
{
	bool ret = false;
	
	sf::Vector2f btn_pos = sprite_.getPosition();
	sf::FloatRect sprite_size = sprite_.getGlobalBounds();

	/*if ((mouse_pos.x > btn_pos.x) && (mouse_pos.x < btn_pos.x + sprite_size.width) &&
		(mouse_pos.y > btn_pos.y) && (mouse_pos.y < btn_pos.y + sprite_size.height))
	{
		ret = true;
	}*/

	return ret;
}

void Button::Render(sf::RenderWindow &window)
{
	window.draw(sprite_);
}