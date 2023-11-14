#pragma once

#include <gui/function_window.hpp>
#include <gui/gui_elements/button.hpp>

class FuncStorage : public Button
{
public:
	FuncStorage()
	{}

	virtual void click() override
	{
		if (isSelected)
			isSelected = false;
		return;
		isSelected = true;
		return;
	}

	void setPosition(sf::Vector2f pos)
	{
		Button::setPosition(pos);
	}

	void setSize(sf::Vector2f size)
	{
		Button::setSize(size);
	}

	void setFont(sf::Font& font)
	{
		Button::setFont(font);
	}

	void drawTo(sf::RenderWindow& window)
	{
		Button::drawTo(window);
	}

	void select()
	{
		isSelected = true;
	}

	void deselect()
	{
		isSelected = false;
	}

private:
	bool isSelected = false;

	functions::func_ff stored_func;
	std::vector<int> sample;
};