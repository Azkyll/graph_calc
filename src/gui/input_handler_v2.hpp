#pragma once

#include <SFML/Graphics.hpp>
#include <gui/function_window.hpp>
#include <gui/gui_elements/textbox.hpp>

#include <unicode-enum.h>

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
		inputLogic(input.text.unicode);
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
		fWindow->drawGraph(storedFunction);
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
			case U::CARRIAGE_RETURN:
				storeFunction();
				inputBuffer = { "" };
				Textbox::clear();
				storedFunction = functions::id<float>;
				current_index = 0;
				return;

			case U::LEFT_PARENTHESIS:
				inputBuffer.push_back("");
				current_index++;
				break;

			case U::RIGHT_PARENTHESIS:
				current_index--;
				break;

			default:
				break;
		}

		if ((charTyped >= U::LATIN_SMALL_LETTER_A && charTyped <= U::LATIN_SMALL_LETTER_Z) || (charTyped >= U::DIGIT_ZERO && charTyped <= U::DIGIT_NINE))
		{
			inputBuffer[current_index].push_back((char)charTyped);
		}

		Textbox::inputLogic(charTyped);
	}
};
