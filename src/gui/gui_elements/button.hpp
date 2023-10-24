#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button()
	{}
	Button(const sf::Vector2f newAnchor, sf::Vector2f newSize, const std::string newText)
	{
		text.setString(newText);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold);
		text.setFillColor(sf::Color::Black);
		button.setPosition(newAnchor);
		button.setFillColor(sf::Color::White);
		button.setSize(newSize);
		text.setPosition(newAnchor);
	}

	Button(const sf::Vector2f newSize, const std::string newText, const sf::Color backColor, const sf::Color fillColor)
	{
		text.setString(newText);
		button.setSize(newSize);
		button.setFillColor(backColor);
		text.setFillColor(fillColor);
		text.setCharacterSize(30);
	}

	void setFont(sf::Font& font)
	{
		text.setFont(font);
	}

	bool isIn(sf::Vector2f point)
	{
		sf::Vector2f anchor = button.getPosition();
		sf::Vector2f size = button.getSize();
		return (
			point.x >= anchor.x && point.x <= anchor.x + size.x && point.y >= anchor.y && point.y <= anchor.y + size.y);
	}

	bool isIn(sf::Vector2i point)
	{
		sf::Vector2f anchor = button.getPosition();
		sf::Vector2f size = button.getSize();
		return (
			point.x >= anchor.x && point.x <= anchor.x + size.x && point.y >= anchor.y && point.y <= anchor.y + size.y);
	}

	bool isMouseIn(sf::RenderWindow& window)
	{
		return isIn(sf::Mouse::getPosition(window));
	}

	void setFillColor(sf::Color color)
	{
		button.setFillColor(color);
	}

	void setPosition(sf::Vector2f pos)
	{
		button.setPosition(pos);
		float buttWidth = button.getLocalBounds().width;
		float buttHeight = button.getLocalBounds().height;
		float textWidth = text.getLocalBounds().width;
		float textHeight = text.getLocalBounds().height;

		float newTextX = pos.x + (buttWidth - textWidth) * 0.5f;
		float newTextY = pos.y + (buttHeight - textHeight) * 0.5f;
		text.setPosition({ newTextX, newTextY });
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
	}

	sf::Vector2f getSize()
	{
		return button.getSize();
	}

	sf::Vector2f getPosition()
	{
		return button.getPosition();
	}

	void setTextFillColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	void setHeld(bool held)
	{
		isHeld = held;
	}

	bool isBtnHeld()
	{
		return isHeld;
	}

	void setToDefColor()
	{
		button.setFillColor(bgColor);
	}

	void setToHoveredColor()
	{
		button.setFillColor(hoveredColor);
	}

	void setToHeldColor()
	{
		button.setFillColor(heldColor);
	}

	void setSize(sf::Vector2f size)
	{
		button.setSize(size);
	}

	void setDefColor(sf::Color color)
	{
		bgColor = color;
	}

	void setHoveredColor(sf::Color color)
	{
		hoveredColor = color;
	}

	void setHeldColor(sf::Color color)
	{
		heldColor = color;
	}

	void setClickedColor(sf::Color color)
	{
		clickedColor = color;
	}

	void setText(std::string str)
	{
		text.setString(str);
	}

private:
	sf::Text text;
	sf::RectangleShape button;
	sf::Color bgColor = sf::Color::White;
	sf::Color hoveredColor = sf::Color::Red;
	sf::Color heldColor = sf::Color::Magenta;
	sf::Color clickedColor = sf::Color::Yellow;
	bool isHeld = false;
};