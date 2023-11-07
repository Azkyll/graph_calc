#pragma once

#include <functions/composite_function.hpp>

#include <SFML/Graphics.hpp>
#include <gui/function_window.hpp>
#include <gui/gui_elements/textbox.hpp>

using Keyboard = sf::Keyboard;

enum Operations
{
	none,
	add,
	substract,
	multiply,
	divide
};

class InputBox : public Textbox
{
public:
	InputBox()
	{}

	InputBox(GraphWindow& window) :
		fWindow { &window }
	{}

	InputBox(GraphWindow& window, sf::Vector2f position) :
		fWindow { &window }
	{
		setCharacterSize(30);
		setSelected(false);
		setPosition(position);
	}

	void typing(sf::Event input)
	{
		int charTyped = input.text.unicode;
	}

	void drawTo(sf::RenderWindow& window)
	{
		Textbox::drawTo(window);
	}

	void setFont(sf::Font& font)
	{
		Textbox::setFont(font);
	}

	bool getSelected()
	{
		return isSelected;
	}

	void createFunction()
	{
	}

private:
	GraphWindow* fWindow = nullptr;
	std::vector<std::string> inputBuffer = { "" };
	uint32_t current_index = 0;

	Operations storedOperation = none;

	void deleteLastCharacter()

	{
		Textbox::deleteLastCharacter();
	}

	void inputLogic(int charTyped)
	{
		switch (charTyped)
		{
			case Keyboard::Enter:
				createFunction();
				inputBuffer.clear();
				Textbox::clear();
				return;

			case Keyboard::LBracket:
				inputBuffer.push_back("");
				current_index++;

			case Keyboard::RBracket:
				current_index--;

			default:
				break;
		}

		Textbox::inputLogic(charTyped);
	}
};
