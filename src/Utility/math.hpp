#pragma once
#include <SFML/Graphics.hpp>

inline float dotProd(const sf::Vector2f v1, const sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline float norm(const sf::Vector2f v)
{
	return sqrt(dotProd(v, v));
}

inline float distance(const sf::Vector2f v1, const sf::Vector2f v2)
{
	return norm(v2 - v1);
}

struct Lerp1D
{
	float start { 0.f };
	float end { 1.f };
	float t { 0.5f };

	Lerp1D()
	{}
	Lerp1D(const float a, const float b) :
		start { a },
		end { b }
	{}
	Lerp1D(const float a, const float b, const float t_) :
		start { a },
		end { b },
		t { t_ }
	{}

	float lerp()
	{
		return start + (end - start) * t;
	}

	float lerp(const float t_)
	{
		return start + (end - start) * t_;
	}

	void advanceTime(const float dt)
	{
		t += dt;
	}
};

class Lerp2D
{
public:
	Lerp2D()
	{}
	Lerp2D(const sf::Vector2f a, const sf::Vector2f b) :
		start { a },
		end { b },
		dv { b - a }
	{}

	sf::Vector2f lerp()
	{
		return start + dv * t;
	}

	sf::Vector2f lerp(const float t_)
	{
		return start + dv * t_;
	}

	void advanceTime(float dt)
	{
		if (t == 1)
		{
			return;
		}
		t += dt;
	}

	void setStartPoint(sf::Vector2f p)
	{
		start = p;
		dv = end - start;
	}

	void setEndPoint(sf::Vector2f p)
	{
		end = p;
		dv = end - start;
	}

	void setEndPoints(sf::Vector2f a, sf::Vector2f b)
	{
		start = a;
		end = b;
		dv = b - a;
	}

	std::vector<sf::Vector2f> getEndPoints()
	{
		return { start, end };
	}

	sf::Vector2f getStartPoint()
	{
		return start;
	}

	sf::Vector2f getEndPoint()
	{
		return end;
	}

private:
	sf::Vector2f start {};
	sf::Vector2f end {};
	sf::Vector2f dv {};
	float t { 0.f };
};