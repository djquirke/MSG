#pragma once
#include <SFML\Graphics.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Initialise(const sf::Vector2f &pos, int w, int h, int mw, int mh);
	void setOffset(sf::Vector2f &offset);
	sf::Vector2f getPosition() { return pos_; }
	void setCamera(const sf::Vector2f &player_pos);

private:
	sf::IntRect rect_;
	int width_, height_, map_width_, map_height_;
	sf::Vector2f pos_;
	sf::Vector2f offset_;

	void UpdateRect();
};

