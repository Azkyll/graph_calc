#pragma once
#include <SFML/Graphics.hpp>
#include <Utility/math.hpp>
#include <gui/sfLine.hpp>

class Slider
{
public:
	Slider()
	{}
	Slider(sf::Vector2f newCenter, std::string newText) :
		radius { 15 },
		center { newCenter }
	{
		circle.setFillColor(sf::Color::White);
		circle.setPointCount(32);
		circle.setRadius(radius);
		circle.setPosition(newCenter - sf::Vector2f { 15, 15 });

		text.setString(newText);
		text.setFillColor(sf::Color::White);
		text.setPosition(center + sf::Vector2f { -20, 60 });
		text.setCharacterSize(30);

		tParam.setString("0.5");
		tParam.setFillColor(sf::Color::White);
		tParam.setPosition(center + sf::Vector2f { 70, -70 });
		tParam.setCharacterSize(15);
	}

	void setFont(sf::Font& font)
	{
		text.setFont(font);
		tParam.setFont(font);
	}

	void drawTo(sf::RenderWindow& window)
	{
		sfLine line(center - sf::Vector2f { width, 0 }, center + sf::Vector2f { width, 0 });
		line.setThickness(5);
		window.draw(line);
		window.draw(circle);

		window.draw(text);

		updatePDisplay();
		window.draw(tParam);
	}

	void move(sf::Vector2i pos)
	{
		float rad = circle.getRadius();
		sf::Vector2f sp = center - sf::Vector2f { width, 0 };
		sf::Vector2f ep = center + sf::Vector2f { width, 0 };

		if (pos.x <= sp.x || pos.x >= ep.x || pos.y >= center.y + 3 * rad || pos.y <= center.y - 3 * rad)
		{
			return;
		}

		float newX = pos.x - circle.getRadius();
		circle.setPosition({ newX, circle.getPosition().y });
	}

	void move(sf::RenderWindow& window)
	{
		move(sf::Mouse::getPosition(window));
	}

	bool isIn(sf::Vector2f pos)
	{
		float rad = circle.getRadius();
		sf::Vector2f center = circle.getPosition() + rad * sf::Vector2f { 1, 1 };
		return (distance(pos, center) <= rad);
	}

	bool isMouseIn(sf::RenderWindow& window)
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		sf::Vector2f pos_ = { (float)pos.x, (float)pos.y };
		return isIn(pos_);
	}

	void Hovered()
	{
		circle.setFillColor(sf::Color::Red);
	}

	void unHovered()
	{
		circle.setFillColor(sf::Color::White);
	}

	float getParameter()
	{
		float a = center.x - width * 0.5f;
		float c = circle.getPosition().x + radius;
		return (c - a) * 0.5f / width + 0.25f;
	}

	void updatePDisplay()
	{
		float t = std::round(getParameter() * 100.f) / 100.f;
		tParam.setString(std::to_string(t).substr(0, 4));
	}

private:
	float radius { 15 };
	sf::CircleShape circle;
	sf::Vector2f center;
	float width { 200.f };
	sf::Text text;
	sf::Text tParam;
};