#pragma once

#include <algorithm>
#include <functional>
#include <iterator>

struct FourierSeries
{
	FourierSeries()
	{}

	FourierSeries(std::vector<float> s_n, std::vector<float> c_m) :
		sine_coefficients { s_n },
		cos_coefficients { c_m }
	{}

	float compute(float x)
	{
		float s = 0;
		if(cos_coefficients.size() != 0)
			s += cos_coefficients.front();
		for (unsigned int i = 0; i < sine_coefficients.size(); i++)
		{
			s += std::sin((i + 1) * x) * sine_coefficients[i];
		}
		for (unsigned int i = 1; i < cos_coefficients.size(); i++)
		{
			s += std::cos((i) * x) * cos_coefficients[i];
		}
		return s;
	}

	FourierSeries operator+(FourierSeries& series)
	{
		int size_s = std::min(sine_coefficients.size(), series.sine_coefficients.size());
		int size_c = std::min(cos_coefficients.size(), series.cos_coefficients.size());
		std::vector<float> s_sum(size_s);
		std::vector<float> c_sum(size_c);

		std::transform(
			begin(sine_coefficients), begin(sine_coefficients) + size_s, begin(series.sine_coefficients), begin(s_sum), std::plus<float>());

		std::transform(
			begin(cos_coefficients), begin(cos_coefficients) + size_c, begin(series.cos_coefficients), begin(c_sum), std::plus<float>());

		return FourierSeries(s_sum, c_sum);
	}

	FourierSeries operator-(FourierSeries& series)
	{
		int size_s = std::min(sine_coefficients.size(), series.sine_coefficients.size());
		int size_c = std::min(cos_coefficients.size(), series.cos_coefficients.size());
		std::vector<float> s_sum(size_s);
		std::vector<float> c_sum(size_c);

		std::transform(
			begin(sine_coefficients), begin(sine_coefficients) + size_s, begin(series.sine_coefficients), begin(s_sum), std::minus<float>());

		std::transform(
			begin(cos_coefficients), begin(cos_coefficients) + size_c, begin(series.cos_coefficients), begin(c_sum), std::minus<float>());

		return FourierSeries(s_sum, c_sum);
	}

	bool operator==(FourierSeries& series)
	{
		return sine_coefficients == series.sine_coefficients && cos_coefficients == series.cos_coefficients;
	}

	std::string asString(){
		std::string str;
		for(unsigned int i = 0; i < sine_coefficients.size(); ++i)
		{
			str += std::to_string(sine_coefficients[i]) + " * sin(" + std::to_string(i + 1) +"x) ";
		}

		str += std::to_string(cos_coefficients.front());

		for(unsigned int i = 1; i < cos_coefficients.size(); ++i)
		{
			str += std::to_string(cos_coefficients[i]) + " * cos(" + std::to_string(i) +"x) ";
		}
		return str;
	}

	std::vector<float> sine_coefficients;
	std::vector<float> cos_coefficients;
};