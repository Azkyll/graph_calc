#pragma once

#include <SFML/Graphics.hpp>
#include <gui/function_window.hpp>
#include <gui/gui_elements/textbox.hpp>

using Keyboard = sf::Keyboard;


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
		Textbox::typing(input);
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

	void storeFunction()
	{
		storedFunction = functions::fromBuffer<float>(inputBuffer);
	}

	functions::func_ff getStored()
	{
		return storedFunction;
	}

private:
	GraphWindow* fWindow = nullptr;
	std::vector<std::string> inputBuffer = { "" };
	uint32_t current_index = 0;
	functions::func_ff storedFunction = functions::id<float>;


	void deleteLastCharacter()

	{
		Textbox::deleteLastCharacter();
	}

	void inputLogic(int charTyped)
	{
		switch (charTyped)
		{
			case Keyboard::Enter:
				storeFunction();
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
