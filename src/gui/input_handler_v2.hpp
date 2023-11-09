#pragma once

#include <SFML/Graphics.hpp>
#include <gui/function_window.hpp>
#include <gui/gui_elements/textbox.hpp>
#include <stack>

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
		storedFunction = functionStacks[0].top();
		functionStacks[0].pop();
	}

	void drawFunction()
	{
		fWindow->drawGraph(storedFunction);
	}

	functions::func_ff getStored()
	{
		return storedFunction;
	}

private:
	GraphWindow* fWindow = nullptr;
	std::string inputBuffer = "";
	std::string previous;
	std::vector<std::stack<functions::func_ff>> functionStacks = { {} };
	std::vector<std::stack<functions::Operations>> opStacks = { {} };
	uint32_t current_index = 0;
	functions::func_ff storedFunction = functions::id<float>;

	void deleteLastCharacter()

	{
		Textbox::deleteLastCharacter();
	}

	void emptyLastStacks()
	{
		if (opStacks[current_index].size() == 0 && functionStacks[current_index].size() == 0)
			return;
		while (functionStacks[current_index].size() > 1)
		{
			functions::func_ff g(functionStacks[current_index].top());
			functionStacks[current_index].pop();
			functions::func_ff f(functionStacks[current_index].top());
			functionStacks[current_index].pop();
			functions::Operations op(opStacks[current_index].top());
			opStacks[current_index].pop();
			functionStacks[current_index].emplace(functions::executeOperation<float>(op, f, g));
		}

		functionStacks[current_index - 1].emplace(functionStacks[current_index].top());
		functionStacks[current_index].pop();
		functionStacks.pop_back();
		opStacks.pop_back();
	}

	void inputLogic(int charTyped)
	{
		switch (charTyped)
		{
			case U::CARRIAGE_RETURN:
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				storeFunction();
				drawFunction();
				inputBuffer =  "";
				Textbox::clear();
				storedFunction = functions::id<float>;
				current_index = 0;
				return;

			case U::LEFT_PARENTHESIS:
				previous = inputBuffer;
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";

				if (previous != "+" && previous != "-" && previous != "/" && previous != "^" && previous != "*")
					opStacks[current_index].emplace(functions::COMPOSE);
				functionStacks.push_back({});
				opStacks.push_back({});

				current_index++;
				break;

			case U::RIGHT_PARENTHESIS:
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				previous = inputBuffer;
				inputBuffer = "";
				emptyLastStacks();
				current_index--;
				if (opStacks[current_index].top() == functions::COMPOSE)
				{
					functions::Operations op = opStacks[current_index].top();
					opStacks[current_index].pop();
					functions::func_ff g = functionStacks[current_index].top();
					functionStacks[current_index].pop();
					functions::func_ff f = functionStacks[current_index].top();
					functionStacks[current_index].pop();
					functions::executeOperation<float>(op, f, g);
				}

				break;

			case U::PLUS_SIGN:
				opStacks[current_index].emplace(functions::Operations::ADD);
				previous = inputBuffer;
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";

				break;

			case U::HYPHEN_MINUS:
				opStacks[current_index].emplace(functions::Operations::SUBSTRACT);
				previous = inputBuffer;
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				break;

			case U::ASTERISK:
				opStacks[current_index].emplace(functions::Operations::MULTIPLY);
				previous = inputBuffer;
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				break;

			case U::slash:
				opStacks[current_index].emplace(functions::Operations::DIVIDE);
				previous = inputBuffer;
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				break;

			case U::CIRCUMFLEX_ACCENT:
				opStacks[current_index].emplace(functions::Operations::POWER);
				previous = inputBuffer;
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				break;

			default:
				break;
		}

		// digits, letters, digit point
		if ((charTyped >= U::LATIN_SMALL_LETTER_A && charTyped <= U::LATIN_SMALL_LETTER_Z) || (charTyped >= U::DIGIT_ZERO && charTyped <= U::DIGIT_NINE) || charTyped == U::period)
		{
			inputBuffer.push_back((char)charTyped);
		}

		Textbox::inputLogic(charTyped);
	}
};
