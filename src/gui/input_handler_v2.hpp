#pragma once

#include <stack>
#include <SFML/Graphics.hpp>
#include <gui/function_window.hpp>
#include <gui/gui_elements/textbox.hpp>
#include <gui/stored_sample.hpp>

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
		functionStacks.emplace(std::stack<functions::func_ff>());
		opStacks.emplace(std::stack<functions::Operations>());
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
		storedFunction = functionStacks.top().top();
		functionStacks.top().pop();
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
	std::stack<std::stack<functions::func_ff>> functionStacks;
	std::stack<std::stack<functions::Operations>> opStacks;
	functions::func_ff storedFunction = functions::id<float>;

	void deleteLastCharacter()

	{
		Textbox::deleteLastCharacter();
	}

	void executeLastOperation()
	{
		functions::func_ff g(functionStacks.top().top());
		functionStacks.top().pop();
		functions::func_ff f(functionStacks.top().top());
		functionStacks.top().pop();
		functions::Operations op(opStacks.top().top());
		opStacks.top().pop();
		functionStacks.top().emplace(functions::executeOperation<float>(op, f, g));
	}

	void closeLastStack()
	{
		while (opStacks.top().size() > 0)
		{
			executeLastOperation();
		}
		functions::func_ff f = functionStacks.top().top();
		functionStacks.pop();
		opStacks.pop();

		functionStacks.top().emplace(f);
	}

	void inputLogic(int charTyped)
	{
		switch (charTyped)
		{
			case U::CARRIAGE_RETURN:
				if (inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));
				while (functionStacks.size() > 1)
					closeLastStack();
				while (opStacks.top().size() != 0)
					executeLastOperation();
				storeFunction();
				drawFunction();
				inputBuffer = "";
				Textbox::clear();
				return;

			case U::LEFT_PARENTHESIS:
				if(inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";

				if (previousInputType == operand)
					opStacks.top().emplace(functions::COMPOSE);
				functionStacks.emplace();
				opStacks.emplace();
				previousInputType = operation;

				break;

			case U::RIGHT_PARENTHESIS:
				if (inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				closeLastStack();
				previousInputType = operation;

				if (opStacks.top().size() != 0)
				{
					if ((opStacks.top().top() == functions::COMPOSE || opStacks.top().top() == functions::POWER) && opStacks.top().size() == 1)
					{
						executeLastOperation();
					}
				}

				break;

			case U::PLUS_SIGN:
				opStacks.top().emplace(functions::Operations::ADD);
				if (inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));
				inputBuffer = "";
				previousInputType = operation;

				break;

			case U::HYPHEN_MINUS:
				if (inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));

				opStacks.top().emplace(functions::Operations::SUBSTRACT);
				inputBuffer = "";
				previousInputType = operation;
				break;

			case U::ASTERISK:
				if (inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));
				opStacks.top().emplace(functions::Operations::MULTIPLY);
				inputBuffer = "";
				previousInputType = operation;
				break;

			case U::slash:
				if (inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));
				opStacks.top().emplace(functions::Operations::DIVIDE);
				inputBuffer = "";
				previousInputType = operation;
				break;

			case U::CIRCUMFLEX_ACCENT:
				if (inputBuffer != "")
					functionStacks.top().emplace(functions::fromString<float>(inputBuffer));
				opStacks.top().emplace(functions::Operations::POWER);
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
