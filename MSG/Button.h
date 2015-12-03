#pragma once

#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics.hpp>

class Button
{
public:
	Button() : norm_texture_(), hover_texture_(), sprite_(), is_selected_(false) {};
	~Button();

	bool Initialise(const std::string &norm_path, const std::string &hover_path,
					const sf::Vector2f &pos, bool selected);
	void Update();
	void Render(sf::RenderWindow &window);

	bool IsSelected() { return is_selected_; }
	void setSelected(bool selected) { is_selected_ = selected; }

private:
	sf::Texture norm_texture_;
	sf::Texture hover_texture_;
	sf::Sprite sprite_;
	bool is_selected_;
};

