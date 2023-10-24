#pragma once

#include <functions/fourier.hpp>
#include <functions/polynomial.hpp>

class SumFunction
{
public:
	SumFunction()
	{}

	SumFunction(Polynomial p, FourierSeries s) :
		pol { p },
		series { s }
	{}

	SumFunction(std::vector<float> polyCoeff, std::vector<float> sineCoeff, std::vector<float> cosCoeff) :
		pol { polyCoeff },
		series { sineCoeff, cosCoeff }
	{}

	SumFunction(Polynomial p) :
		pol { p },
		series { { 0 }, { 0 } }
	{}

	SumFunction(FourierSeries s) :
		pol { { 0 } },
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
		return pol == sf.pol && series == sf.series;
	}

	SumFunction operator+(SumFunction sf)
	{
		return SumFunction(pol + sf.pol, series + sf.series);
	}

	SumFunction operator-(SumFunction sf)
	{
		return SumFunction(pol - sf.pol, series - sf.series);
	}

private:
	Polynomial pol;
	FourierSeries series;
};

class ProdFunction
{
public:
	ProdFunction()
	{}

	ProdFunction(SumFunction sf1_, SumFunction sf2_) :
		sf1 { sf1_ },
		sf2 { sf2_ }
	{}

	ProdFunction(SumFunction sfunc) :
		sf1 { sfunc },
		sf2 { { 1 }, {}, {} }
	{}

	float compute(float x)
	{
		return sf1.compute(x) * sf2.compute(x);
	}

private:
	SumFunction sf1;
	SumFunction sf2;
};

