#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

struct Polynomial
{
	Polynomial()
	{}

	Polynomial(std::vector<float> newCoeff) :
		coeff { newCoeff },
		order { newCoeff.size() - 1}
	{}

	Polynomial operator+(Polynomial p)
	{
		int order = std::max(coeff.size(), p.coeff.size());
		std::vector<float> sum_c;
		std::transform(
			begin(coeff), begin(coeff) + order, begin(p.coeff), begin(sum_c), std::plus<float>());
		return Polynomial(sum_c);
	}

	Polynomial operator-(Polynomial p)
	{
		int order = std::max(coeff.size(), p.coeff.size());
		std::vector<float> diff_c;
		std::transform(
			begin(coeff), begin(coeff) + order, begin(p.coeff), begin(diff_c), std::minus<float>());
		return Polynomial(diff_c);
	}

	bool operator==(Polynomial p){
		return coeff == p.coeff;
	}

	float compute(float x)
	{
		float s = 0;
		for (unsigned int i = 0; i < coeff.size(); ++i)
		{
			s += coeff[i] * std::pow(x, i);
		}
		return s;
	}

	std::string asString()
	{
		std::string str;
		str += std::to_string(coeff.front());
		for (unsigned int i = 1; i < order; i++)
		{
			str += " + " + std::to_string(coeff[i]) + "* x^" + std::to_string(i);
		}
		return str;
	}

	std::vector<float> coeff;
	unsigned int order;
};