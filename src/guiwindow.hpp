#pragma once

#include <composite_function.hpp>
#include <function_window.hpp>
#include <gui/button.hpp>
#include <input_handler.hpp>

class GuiWindow
{
public:
	GuiWindow()
	{
		functions.reserve(10);
	}

	GuiWindow(sf::Vector2f newPosition, sf::Vector2f newSize, GraphWindow& win) :
		position { newPosition },
		size { newSize },
		window { &win },
		clearBtn { { position + sf::Vector2f { 10, size.y * 0.6f + 100 } }, { 150, 100 }, "Clear" },
		deleteBtn { { position + sf::Vector2f { 10, size.y * 0.6f + 210 } }, { 150, 100 }, "Delete" }
	{
		window->setSize({ size.x * 0.75f, size.y * 0.6f });
		window->setPosition(position);

		clearBtn.setTextFillColor(sf::Color::Black);
		deleteBtn.setTextFillColor(sf::Color::Black);

		functions.reserve(10);
	}

	GuiWindow(sf::Vector2f newPosition, sf::Vector2f newSize) :
		position { newPosition },
		size { newSize },
		clearBtn { { position + sf::Vector2f { 10, size.y * 0.6f + 100 } }, { 150, 100 }, "Clear" },
		deleteBtn { { position + sf::Vector2f { 10, size.y * 0.6f + 210 } }, { 150, 100 }, "Delete" }
	{
		window = new GraphWindow(position, { size.x * 0.75f, size.y * 0.6f }, {-10, 10}, {-10, 10});
		functions.reserve(10);
	}

	void drawTo(sf::RenderWindow& w)
	{
		//clearBtn.drawTo(w);
		//deleteBtn.drawTo(w);
		window->drawTo(w);
	}

	void deleteFunction(SumFunction func)
	{
		functions.erase(std::remove(functions.begin(), functions.end(), func), functions.end());
		window->clear();
		for (SumFunction f : functions)
			window->drawGraph(f);
	}

	void deleteFunction()
	{
		if(functions.size()==0)
			return;
		functions.pop_back();
		window->clear();
		for (SumFunction f : functions)
			window->drawGraph(f);
	}

	void addFunction(SumFunction func)
	{
		functions.push_back(func);
		window->drawGraph(func);
	}

	void setFont(sf::Font& font)
	{
		clearBtn.setFont(font);
		deleteBtn.setFont(font);
	}

	bool isInDelBtn(sf::Vector2i point)
	{
		return deleteBtn.isIn(point);
	}

	bool isInClearBtn(sf::Vector2i point)
	{
		return clearBtn.isIn(point);
	}

	bool isInDelBtn(sf::RenderWindow& w)
	{
		return deleteBtn.isMouseIn(w);
	}

	bool isInClearBtn(sf::RenderWindow& w)
	{
		return clearBtn.isMouseIn(w);
	}

	void clear()
	{
		window->clear();
		functions.clear();
	}

private:
	sf::Vector2f position = {};
	sf::Vector2f size = {};

	std::vector<SumFunction> functions;

	GraphWindow* window = nullptr;
	Button clearBtn;
	Button deleteBtn;
};
