#pragma once
#include <function_window.hpp>
#include <input_handler.hpp>

class FnBox
{
public:
	FnBox()
	{}

	FnBox(GraphWindow& window, sf::Vector2f position) :
		btn {position, {200, 100}, "Test"},
		input { window, position }
	{
		btn.setFillColor(sf::Color::Red);
	}

	FnBox(GraphWindow& window, sf::Vector2f position, sf::Vector2f size) :
		btn {position, size, "Test"},
		input { window, position }
	{
		btn.setFillColor(sf::Color::Red);
		input.setSelected(true);
	}

	void setFont(sf::Font& font)
	{
		btn.setFont(font);
		input.setFont(font);
	}

	bool isMouseIn(sf::RenderWindow& window)
	{
		return btn.isMouseIn(window);
	}

	void typing(sf::Event event)
	{
		if(not(input.getSelected()))
			return;
		btn.setText("");
		input.typing(event);
	}

	void drawTo(sf::RenderWindow& window)
	{
		btn.drawTo(window);
		input.drawTo(window);
	}

private:
	Button btn;
	InputBox input;
	SumFunction func;
};