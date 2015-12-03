#include "MenuButtonStrip.h"
#include <Windows.h>
#include "KeyboardHandler.h"
#include "GameManager.h"


MenuButtonStrip::~MenuButtonStrip()
{
}

void MenuButtonStrip::Initialise(Alignment direction)
{
	vec_btn_ = std::vector<Button>();
	direction_ = direction;

	if (direction == HORIZONTAL)
	{
		next_key_ = sf::Keyboard::Right;
		prev_key_ = sf::Keyboard::Left;
	}
	else
	{
		next_key_ = sf::Keyboard::Down;
		prev_key_ = sf::Keyboard::Up;
	}
}

void MenuButtonStrip::AddButton(Button &btn)
{
	vec_btn_.push_back(btn);
}

bool MenuButtonStrip::AddButton(const std::string &norm_path, const std::string &hover_path,
								const sf::Vector2f &pos, bool selected)
{
	bool ret = true;

	Button temp = Button();
	if (!temp.Initialise(norm_path, hover_path, pos, selected))
	{
		OutputDebugString(L"Error initialising lobby");
		ret = false;
	}

	vec_btn_.push_back(temp);

	return ret;
}

void MenuButtonStrip::Update()
{
	checkKeyboardInput();

	//update button sprites
	for (auto &btn : vec_btn_)
	{
		btn.Update();
	}
}

void MenuButtonStrip::Render(sf::RenderWindow &window)
{
	for (auto &btn : vec_btn_)
	{
		btn.Render(window);
	}
}

void MenuButtonStrip::checkKeyboardInput()
{
	if (KEYBOARD.onKeyDown(next_key_))
	{
		//next_key_pressed_ = true;
		bool next_val = false;
		std::vector<Button>::iterator old_btn;
		//for (auto &btn : vec_btn_)
		for (std::vector<Button>::iterator it = vec_btn_.begin(); it != vec_btn_.end(); it++)
		{
			if (next_val)
			{
				if (std::distance(it, vec_btn_.end()) >= 1)
				{
					old_btn->setSelected(false);
					it->setSelected(true);
				}
				break;
			}

			if (it->IsSelected())
			{
				//it->setSelected(false);
				old_btn = it;
				next_val = true;
			}
		}
	}
	else if (KEYBOARD.onKeyDown(prev_key_))
	{
		bool prev_val = false;
		
		std::vector<Button>::iterator prev_btn = vec_btn_.begin();

		for (std::vector<Button>::iterator it = vec_btn_.begin(); it != vec_btn_.end(); it++)
		{
			if (it->IsSelected())
			{
				it->setSelected(false);
				prev_val = true;
				break;
			}
			
			prev_btn = it;
		}
		if (prev_val)
		{
			if (prev_btn >= vec_btn_.begin())
			{
				prev_btn->setSelected(true);
			}
		}
	}
	else if (KEYBOARD.onKeyDown(sf::Keyboard::Return))
	{
		GAMEMANAGER.setState("game");
	}
}