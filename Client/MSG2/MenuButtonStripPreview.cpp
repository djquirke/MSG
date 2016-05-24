#include "MenuButtonStripPreview.h"
#include <Windows.h>

bool MenuButtonStripPreview::AddButton(Button &btn, std::string prvw_img_path,
									   sf::Vector2f &prvw_img_pos)
{
	bool ret = true;
	vec_btn_.push_back(btn);
	sf::Texture temp_txtre = sf::Texture();

	if (!temp_txtre.loadFromFile(prvw_img_path))
	{
		OutputDebugString(L"Error loading lobby preview texture");
		ret = false;
	}

	preview_image_.setTexture(temp_txtre);
	preview_image_.setPosition(prvw_img_pos);

	return ret;
}

bool MenuButtonStripPreview::AddButton(const std::string &norm_path, const std::string &hover_path,
									   const sf::Vector2f &pos, bool selected, std::string dest,
									   std::string prvw_img_path, sf::Vector2f &prvw_img_pos)
{
	bool ret = true;
	Button temp_btn = Button();

	if (temp_btn.Initialise(norm_path, hover_path, pos, selected, dest))
	{
		ret = false;
	}

	vec_btn_.push_back(temp_btn);
	sf::Texture temp_txtre = sf::Texture();

	if (!temp_txtre.loadFromFile(prvw_img_path))
	{
		OutputDebugString(L"Error loading lobby preview texture");
		ret = false;
	}

	preview_image_.setTexture(temp_txtre);
	preview_image_.setPosition(prvw_img_pos);

	return ret;
}