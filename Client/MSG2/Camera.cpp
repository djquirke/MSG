#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Initialise(const sf::Vector2f &pos, int w, int h, int mw, int mh)
{
	rect_ = sf::IntRect();
	
	pos_ = sf::Vector2f(pos);
	width_ = w;
	height_ = h;
	map_width_ = mw;
	map_height_ = mh;

	UpdateRect();
}

void Camera::setOffset(sf::Vector2f &offset)
{
	offset_ = offset;
	pos_.x += offset_.x;
	pos_.y += offset_.y;

	UpdateRect();
}

void Camera::setCamera(const sf::Vector2f &player_pos)
{
	pos_.x = player_pos.x + offset_.x;
	pos_.y = player_pos.y + offset_.y;
	UpdateRect();
}

void Camera::UpdateRect()
{
	if (pos_.x < 0) pos_.x = 0;
	if (pos_.y < 0) pos_.y = 0;
	if (pos_.x > map_width_ - width_) pos_.x = map_width_ - width_;
	if (pos_.y > map_height_ - height_) pos_.y = map_height_ - height_;

	rect_.left = pos_.x;
	rect_.top = pos_.y;
	rect_.width = width_;
	rect_.height = height_;
}