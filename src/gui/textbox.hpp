#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
public:
	Textbox() :
		isSelected { false }
	{
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::White);
		text.setString("");
	}

	Textbox(int charSize, sf::Color color, bool selected) :
		isSelected { selected }
	{
		text.setCharacterSize(charSize);
		text.setFillColor(color);
		if (selected)
		{
			text.setString("_");
		}
		else
		{
			text.setString("");
		}
	}

	void setFont(sf::Font& font)
	{
		text.setFont(font);
	}

	void setPosition(sf::Vector2f pos)
	{
		text.setPosition(pos);
	}

	void setLimit(bool b)
	{
		hasLimit = b;
	}

	void setLimit(bool b, int n)
	{
		hasLimit = b;
		characterLimit = n;
	}

	void setLimit(int n)
	{
		characterLimit = n;
		hasLimit = true;
	}

	void setSelected(bool selected)
	{
		isSelected = selected;
		if (selected)
		{
			text.setString(string.str() + "_");
		}
		else
		{
			text.setString(string.str());
		}
	}

	bool getSelected()
	{
		return isSelected;
	}

	void clear()
	{
		text.setString("_");
		string.str("");
	}

	void setText(std::string str)
	{
		string.str(str);
		text.setString(str + "_");
	}

	std::string getString()
	{
		return string.str();
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(text);
	}

	void setCharacterSize(int size)
	{
		text.setCharacterSize(size);
	}

	void typing(sf::Event input)
	{
		int charTyped = input.text.unicode;
		if (!isSelected)
		{
			if (charTyped == ENTER_KEY)
			{
				setSelected(true);
			}
			return;
		}
		if (charTyped == DELETE_KEY && hasLimit && string.str().length() >= characterLimit)
		{
			deleteLastCharacter();
			text.setString(string.str() + "_");
			return;
		}
		inputLogic(charTyped);
	}

	void deleteLastCharacter()
	{
		std::string t_ = string.str();
		std::string temp = "";
		for (uint16_t i = 0; i < t_.size() - 1; i++)
		{
			temp += t_[i];
		}
		string.str("");
		string << temp;
	}

	void inputLogic(int charTyped)
	{
		if (hasLimit && string.str().length() >= characterLimit)
		{
			return;
		}
		if (charTyped == ESCAPE_KEY)
		{
			setSelected(false);
			return;
		}
		if (charTyped == ENTER_KEY)
		{
			return;
		}
		if (charTyped == DELETE_KEY)
		{
			if (string.str().length() == 0)
			{
				return;
			}
			deleteLastCharacter();
			text.setString(string.str() + "_");
			return;
		}
		string << static_cast<char>(charTyped);
		text.setString(string.str() + "_");
	}

	friend class InputBox;

private:
	sf::Text text;
	std::ostringstream string;
	bool isSelected = false;
	bool hasLimit = true;
	uint16_t characterLimit = 30;
};