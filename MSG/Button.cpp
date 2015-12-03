#include "Button.h"
#include <Windows.h>

Button::~Button()
{
}

bool Button::Initialise(const std::string &norm_path, const std::string &hover_path,
						const sf::Vector2f &pos, bool selected)
{
	bool ret = true;

	is_selected_ = selected;

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

void Button::Update()
{
	if (is_selected_)
		sprite_.setTexture(hover_texture_);
	else
		sprite_.setTexture(norm_texture_);
}

void Button::Render(sf::RenderWindow &window)
{
	window.draw(sprite_);
}