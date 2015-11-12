#pragma once

#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics.hpp>

class Button
{
public:
	Button() : norm_texture_(), hover_texture_(), sprite_() {};
	~Button();

	bool Initialise(const std::string &norm_path, const std::string &hover_path,
					const sf::Vector2f &pos);
	void Update(const sf::RenderWindow &window);
	void Render(sf::RenderWindow &window);

private:
	sf::Texture norm_texture_;
	sf::Texture hover_texture_;
	sf::Sprite sprite_;

	bool hasCollided(const sf::RenderWindow &window);
};

