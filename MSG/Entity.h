#pragma once
#include <SFML\Graphics.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	virtual bool Initialise(const std::string &sprite_path, bool alive = false);
	bool isAlive() { return isAlive_; }
	void Render(sf::RenderWindow &window);
	virtual void Update();
	void Destroy();
	sf::Vector2f &getPos() { return position_; }

protected:
	bool isAlive_;
	sf::Sprite sprite_;
	sf::Texture texture_;
	sf::Vector2<float> position_;
	sf::Vector2f prev_pos_;
	int id;
};

