#pragma once
#include <SFML\Graphics.hpp>

struct Lane
{
public:
	sf::Vector2f pos;
	int width;

	Lane(sf::Vector2f position, int w)
	{
		pos = position;
		width = w;
	}
};