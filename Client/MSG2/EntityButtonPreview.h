#pragma once
#include "Entity.h"
#include "Button.h"
class EntityButtonPreview :
	public Entity
{
public:
	EntityButtonPreview() : btn_() {}
	~EntityButtonPreview() {};

	bool Initialise(const std::string &sprite_path, const Button &btn,
		            const sf::Vector2f &prvw_img_pos);

private:
	Button btn_;
};

