#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <SFML/Graphics.hpp>
#include <gui/button.hpp>
#include <sstream>

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

class NumberKey
{
public:
	NumberKey()
	{
		btn = Button({ 500, 500 }, { 100, 100 }, NumberToString(number));
	}

	NumberKey(int num) :
		number { num }
	{
	}

	NumberKey(int num, sf::Vector2f newSize)
	{
	}

	void drawTo(sf::RenderWindow& window)
	{
		btn.drawTo(window);
	}

	void setFont(sf::Font& font)
	{
		btn.setFont(font);
	}

private:
	int number = 0;
	Button btn;
};

class NumPad
{
public:
	NumPad()
	{}
	NumPad(sf::Vector2f newPos, sf::Vector2f newSize) :
		position { newPos },
		size { newSize }
	{
	}

private:
	sf::Vector2f position;
	sf::Vector2f size;

	Button numbers[10];
	Button add;
	Button substract;
	Button multiply;
	Button equals;
};