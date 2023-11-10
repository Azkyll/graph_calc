#pragma once

#include <SFML/Graphics.hpp>
#include <gui/function_window.hpp>
#include <gui/gui_elements/textbox.hpp>
#include <stack>

#include <unicode-enum.h>

enum InputType
{
	operand,
	operation
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
	InputType previousInputType = operation;
	std::vector<std::stack<functions::func_ff>> functionStacks = { {} };
	std::vector<std::stack<functions::Operations>> opStacks = { {} };
	functions::func_ff storedFunction = functions::id<float>;
	uint current_index = 0;

	void deleteLastCharacter()

	{
		Textbox::deleteLastCharacter();
	}

	void executeLastOperation()
	{
		functions::func_ff g(functionStacks[current_index].top());
		functionStacks[current_index].pop();
		functions::func_ff f(functionStacks[current_index].top());
		functionStacks[current_index].pop();
		functions::Operations op(opStacks[current_index].top());
		opStacks[current_index].pop();
		functionStacks[current_index].emplace(functions::executeOperation<float>(op, f, g));
	}

	void closeLastStack()
	{
		while (opStacks[current_index].size() > 0)
		{
			executeLastOperation();
		}

		functionStacks[current_index - 1].emplace(functionStacks[current_index].top());

		functionStacks.pop_back();
		opStacks.pop_back();
		current_index--;
	}

	void inputLogic(int charTyped)
	{
		switch (charTyped)
		{
			case U::CARRIAGE_RETURN:
				if(inputBuffer!="")
					functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				if(current_index > 0)
					closeLastStack();
				storeFunction();
				drawFunction();
				inputBuffer = "";
				Textbox::clear();
				storedFunction = functions::id<float>;
				return;

			case U::LEFT_PARENTHESIS:
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";

				if (previousInputType == operand)
					opStacks[current_index].emplace(functions::COMPOSE);
				current_index++;
				functionStacks.push_back({});
				opStacks.push_back({});

				break;

			case U::RIGHT_PARENTHESIS:
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				closeLastStack();

				if (opStacks[current_index].top() == functions::COMPOSE)
				{
					executeLastOperation();
				}

				break;

			case U::PLUS_SIGN:
				opStacks[current_index].emplace(functions::Operations::ADD);
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				previousInputType = operation;

				break;

			case U::HYPHEN_MINUS:
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));

				opStacks[current_index].emplace(functions::Operations::SUBSTRACT);
				inputBuffer = "";
				previousInputType = operation;
				break;

			case U::ASTERISK:
				opStacks[current_index].emplace(functions::Operations::MULTIPLY);
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				previousInputType = operation;
				break;

			case U::slash:
				opStacks[current_index].emplace(functions::Operations::DIVIDE);
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				previousInputType = operation;
				break;

			case U::CIRCUMFLEX_ACCENT:
				opStacks[current_index].emplace(functions::Operations::POWER);
				functionStacks[current_index].emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				previousInputType = operation;
				break;

			default:
				break;
		}

		// digits, letters, digit point
		if ((charTyped >= U::LATIN_SMALL_LETTER_A && charTyped <= U::LATIN_SMALL_LETTER_Z) || (charTyped >= U::DIGIT_ZERO && charTyped <= U::DIGIT_NINE) || charTyped == U::period)
		{
			inputBuffer.push_back((char)charTyped);
			previousInputType = operand;
		}

		Textbox::inputLogic(charTyped);
	}
};
