#pragma once

#include <SFML/Graphics.hpp>
#include <composite_function.hpp>
#include <fourier.hpp>
#include <grid.hpp>
#include <gui/button.hpp>
#include <polynomial.hpp>

class GraphWindow
{
public:
	GraphWindow()
	{
	}

	GraphWindow(sf::Vector2f newPos, sf::Vector2f newSize) :
		position { newPos },
		size { newSize }
	{}

	GraphWindow(sf::Vector2f newPos, sf::Vector2f newSize, sf::Vector2f newXLims, sf::Vector2f newYLims) :
		position { newPos },
		size { newSize },
		xLimits { newXLims },
		yLimits { newYLims }
	{
		scale.x = (xLimits.y - xLimits.x) / size.x;
		scale.y = (yLimits.y - yLimits.x) / size.y;

		grid = Grid({ 5 / scale.x, 5 / scale.y }, position, size);
		graph.create(size.x, size.y, sf::Color::Black);
		texture.create(size.x, size.y);
	}

	FourierSeries addFunction(FourierSeries ser)
	{
		drawGraph(ser);
		return (ser);
	}

	Polynomial addFunction(Polynomial pol)
	{
		drawGraph(pol);
		return (pol);
	}

	SumFunction addFunction(SumFunction sf)
	{
		drawGraph(sf);
		return (sf);
	}

	void setSize(sf::Vector2f s)
	{
		size = s;
		scale.x = (xLimits.y - xLimits.x) / size.x;
		scale.y = (yLimits.y - yLimits.x) / size.y;
		grid = Grid({ 5 / scale.x, 5 / scale.y }, position, size);
	}

	void setPosition(sf::Vector2f p)
	{
		position = p;
	}

	void setLimits(sf::Vector2f xl, sf::Vector2f yl)
	{
		xLimits = xl;
		yLimits = yl;
	}

	void setXLimits(sf::Vector2f xl)
	{
		xLimits = xl;
	}

	void setYLimits(sf::Vector2f yl)
	{
		yLimits = yl;
	}

	void drawGraph(FourierSeries& series)
	{
		for (float x = xLimits.x; x < xLimits.y; x += scale.x)
		{
			float y = -series.compute(x);
			if (y > yLimits.x && y < yLimits.y)
				graph.setPixel((x - xLimits.x) / scale.x, (y - yLimits.x) / scale.y, sf::Color::White);
		}
		texture.loadFromImage(graph);
	}

	void drawGraph(Polynomial p)
	{
		for (float x = xLimits.x; x < xLimits.y; x += scale.x)
		{
			float y = -p.compute(x);
			if (y > yLimits.x && y < yLimits.y)
				graph.setPixel((x - xLimits.x) / scale.x, (y - yLimits.x) / scale.y, sf::Color::White);
		}
		texture.loadFromImage(graph);
	}

	void drawGraph(SumFunction sF)
	{
		for (float x = xLimits.x; x < xLimits.y; x += scale.x)
		{
			float y = -sF.compute(x);
			if (y > yLimits.x && y < yLimits.y)
				graph.setPixel((x - xLimits.x) / scale.x, (y - yLimits.x) / scale.y, sf::Color::White);
		}
		texture.loadFromImage(graph);
	}

	void drawSum(Polynomial p, FourierSeries f)
	{
		for (float x = xLimits.x; x < xLimits.y; x += scale.x)
		{
			float y = -f.compute(x) - p.compute(x);
			if (y > yLimits.x && y < yLimits.y)
				graph.setPixel((x - xLimits.x) / scale.x, (y - yLimits.x) / scale.y, sf::Color::White);
		}
		texture.loadFromImage(graph);
	}

	void drawSum(FourierSeries f, Polynomial p)
	{
		drawSum(p, f);
	}

	void drawProduct(Polynomial p, FourierSeries f)
	{
		for (float x = xLimits.x; x < xLimits.y; x += scale.x)
		{
			float y = -f.compute(x) * p.compute(x);
			if (y > yLimits.x && y < yLimits.y)
				graph.setPixel((x - xLimits.x) / scale.x, (y - yLimits.x) / scale.y, sf::Color::White);
		}
		texture.loadFromImage(graph);
	}

	void drawProduct(FourierSeries f, Polynomial p)
	{
		drawProduct(p, f);
	}

	void drawTo(sf::RenderWindow& window)
	{
		sf::Sprite spr;
		spr.setTexture(texture);
		spr.setPosition(position);
		window.draw(spr);
		if (showGrid)
			grid.drawTo(window);
	}

	void clear()
	{
		graph = sf::Image();
		graph.create(size.x, size.y, sf::Color::Black);
		texture.loadFromImage(graph);
	}

private:
	// Relative to window
	sf::Vector2f position;
	sf::Vector2f size;

	// For function computation
	sf::Vector2f xLimits;
	sf::Vector2f yLimits;

	sf::Vector2f scale;

	// To draw
	sf::Vector2f origin;
	bool showGrid = true;
	Grid grid;
	sf::Image graph;
	sf::Texture texture;
};
