#pragma once
#include <SFML\Graphics.hpp>
#include "Lane.h"

class Entity
{
public:
	Entity();
	~Entity();

	virtual bool Initialise(const std::string &sprite_path, bool alive = false, bool collidable = false);
	void setTag(std::string tag) { tag_ = tag; }
	std::string getTag() { return tag_; }
	bool isAlive() { return isAlive_; }
	bool isCollidable() { return isCollidable_; }
	void Render(sf::RenderWindow &window);
	virtual void Update();
	void Destroy();
	sf::Vector2f &getPos() { return position_; }
	float getHeight() { return sprite_.getGlobalBounds().height; }
	float getWidth() { return sprite_.getGlobalBounds().width; }
	sf::FloatRect getRect();
	void setPos(const sf::Vector2f &pos) { position_ = pos; }
	void setLane(int num, const Lane &lane);
	int getLane() { return lane_; }

protected:
	bool isAlive_;
	bool isCollidable_;
	sf::Sprite sprite_;
	sf::Texture texture_;
	sf::Vector2<float> position_;
	sf::Vector2f prev_pos_;
	int id_;
	std::string tag_;
	int lane_ = 0;
};

