#pragma once
#include <functional>
#include <iostream>

#define ZERO 48
#define ONE 49
#define NINE 57
#define LETTER_a 97
#define LETTER_z 122
#define LETTER_x 120
#define FULL_STOP 46

namespace functions
{
enum Operations
{
	NONE,
	ADD,
	MULTIPLY,
	SUBSTRACT,
	DIVIDE
};

template <typename T>
std::function<T(T)> sum(std::function<T(T)> f, std::function<T(T)> g)
{
	return [f, g](T x) {
		return f(x) + g(x);
	};
}

template <typename T>
std::function<T(T)> product(std::function<T(T)> f, std::function<T(T)> g)
{
	return [f, g](T x) {
		return f(x) * g(x);
	};
}

template <typename T>
std::function<T(T)> difference(std::function<T(T)> f, std::function<T(T)> g)
{
	return [f, g](T x) {
		return f(x) - g(x);
	};
}

template <typename T>
std::function<T(T)> quotient(std::function<T(T)> f, std::function<T(T)> g)
{
	return [f, g](T x) {
		return f(x) / g(x);
	};
}

template <typename T>
std::function<T(T)> pow(std::function<T(T)> f, T n)
{
	return [f, n](T x) {
		return std::pow(f(x), n);
	};
}

const double PI = 3.141592653589793238462643;

typedef std::function<double(double)> func_dd;
typedef std::function<float(float)> func_ff;
typedef std::function<int(int)> func_ii;

template <typename T>
std::function<T(T)> id = [](T x) { return x; };

template <typename T>
std::function<T(T)> constant_one = [](T x) { return 1; };

template <typename T>
std::function<T(T)> exp = [](T x) { return std::exp(x); };
template <typename T>
std::function<T(T)> log = [](T x) { return std::log(x); };

template <typename T>
std::function<T(T)> cos = [](T x) { return std::cos(x); };
template <typename T>
std::function<T(T)> sin = [](T x) { return std::sin(x); };
template <typename T>
std::function<T(T)> tan = [](T x) { return std::tan(x); };

template <typename T>
std::function<T(T)> cosh = [](T x) { return 0.5 * (std::exp(x) + std::exp(-x)); };
template <typename T>
std::function<T(T)> sinh = [](T x) { return 0.5 * (std::exp(x) - std::exp(-x)); };
template <typename T>
std::function<T(T)> tanh = [](T x) { return sinh<T>(x) / cosh<T>(x); };

template <typename F0, typename... F>
class Composer2
{
	F0 f0_;
	Composer2<F...> tail_;

public:
	Composer2(F0 f0, F... f) :
		f0_(f0),
		tail_(f...)
	{}

	template <typename T>
	T operator()(const T& x) const
	{
		return f0_(tail_(x));
	}
};

template <typename F>
class Composer2<F>
{
	F f_;

public:
	Composer2(F f) :
		f_(f)
	{}

	template <typename T>
	T operator()(const T& x) const
	{
		return f_(x);
	}
};

template <typename... F>
Composer2<F...> compose2(F... f)
{
	return Composer2<F...>(f...);
}

template <typename T>
std::function<T(T)> fromString(std::string input)
{
	std::function<T(T)> selected_function = functions::id<T>;
	Operations storedOperation = none;

	// provide function string as ax + bx
	//

	if (input == "x")
	{
		return selected_function;
	}

	std::string buffer = "";
	double numBuffer = 0;
	bool inDecimals = false;
	uint decimalDepth = 0;

	for (size_t i = 0; i < input.length(); i++)
	{
		char c = input[i];
		if (c >= ZERO && c <= NINE)
		{
			if (inDecimals)
			{
				decimalDepth++;
				numBuffer += std::pow(0.1, decimalDepth) * (c - ZERO);
			}
			else
			{
				numBuffer = 10 * numBuffer + c - ZERO;
			}
		}

		if (c == FULL_STOP)
		{
			inDecimals = true;
		}

		if (c >= LETTER_a && c <= LETTER_z)
		{
			buffer.push_back(c);
		}
	}

	if (buffer == "x")
		selected_function = functions::id<T>;

	if (buffer == "exp")
		selected_function = functions::exp<T>;

	if (buffer == "log")
		selected_function = functions::log<T>;

	if (buffer == "cos")
		selected_function = functions::cos<T>;

	if (buffer == "sin")
		selected_function = functions::sin<T>;

	if (buffer == "tan")
		selected_function = functions::tan<T>;

	if (buffer == "cosh")
		selected_function = functions::cosh<T>;

	if (buffer == "sinh")
		selected_function = functions::sinh<T>;

	if (buffer == "tanh")
		selected_function = functions::tanh<T>;

	if (numBuffer == 0 && buffer != "x")
	{
		numBuffer += 1;
	}

	return [numBuffer, selected_function](T x) {
		return static_cast<T>(numBuffer * selected_function(x));
	};
}

template <typename T>
std::function<T(T)> fromBuffer(std::vector<std::string> inputBuffer)
{
	std::function<T(T)> current_function = functions::id<T>;
	for (size_t i = inputBuffer.size(); i > 0; i--)
	{
		std::string current_string = inputBuffer[i - 1];
		current_function = compose2(fromString<T>(current_string), current_function);
	}
	return current_function;
}

}
