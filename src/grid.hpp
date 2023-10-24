#pragma once

#include <SFML/Graphics.hpp>
#include <gui/sfLine.hpp>

class Grid
{
public:
	Grid()
	{}

	Grid(float xp, float yp, sf::Vector2f newP, sf::Vector2f newSize) :
		period { xp, yp },
		origin { newP },
		size { newSize }
	{}

	Grid(sf::Vector2f newPer, sf::Vector2f newPos, sf::Vector2f newSize) :
		period { newPer },
		origin { newPos },
		size { newSize }
	{}

	void drawTo(sf::RenderWindow& window)
	{
		float nPeriodsX = (int)(size.x / period.x);
		float nPeriodsY = (int)(size.y / period.y);

		for (int i = 0; i <= nPeriodsX; ++i)
		{
			window.draw(sfLine({ origin.x + i * period.x, origin.y }, { origin.x + i * period.x, origin.y + size.y }));
		}

		for (int i = 0; i <= nPeriodsY; ++i)
		{
			window.draw(sfLine({ origin.x, origin.y + i * period.y }, { origin.x + size.x, origin.y + i * period.y }));
		}
	}

private:
	sf::Vector2f period;

	sf::Vector2f origin;
	sf::Vector2f size;
};