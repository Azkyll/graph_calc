#pragma once

#include <fourier.hpp>
#include <polynomial.hpp>

class SumFunction
{
public:
	SumFunction()
	{}

	SumFunction(Polynomial p, FourierSeries s) :
		pol { p },
		series { s }
	{}

	float compute(float x)
	{
		float s = 0;
		s += pol.compute(x);
		s += series.compute(x);
		return s;
	}

	std::string asString()
	{
		return pol.asString() + " " + series.asString();
	}

	bool operator==(SumFunction sf)
	{
		return pol==sf.pol && series==sf.series;
	}

private:
	Polynomial pol;
	FourierSeries series;
};
