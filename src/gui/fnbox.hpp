#pragma once
#include <gui/function_window.hpp>
#include <gui/input_handler.hpp>

class FnBox
{
public:
	FnBox()
	{}

	FnBox(GraphWindow& window, sf::Vector2f position) :
		btn { position, { 450, 150 }, "Test" },
		input { window, position }
	{
		btn.setFillColor(sf::Color::Red);
		input.setSelected(true);
	}

	FnBox(GraphWindow& window, sf::Vector2f position, sf::Vector2f size) :
		btn { position, size, "Test" },
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
		if (isFull)
		{
			setSelected(false);
			return;
		}
		if (event.text.unicode == ENTER_KEY && !getSelected())
			setSelected(true);

		if (not(getSelected()))
			return;
		btn.setText("");
		input.typing(event);
	}

	void drawTo(sf::RenderWindow& window)
	{
		btn.drawTo(window);
		input.drawTo(window);
	}

	void setSelected(bool sel)
	{
		input.setSelected(sel);
	}

	bool getSelected()
	{
		return input.getSelected();
	}

	// TODO overload

private:
	Button btn;
	InputBox input;
	ProdFunction func;
	bool isFull = false;
};