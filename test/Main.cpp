#include <functional>
#include <iostream>

#define ZERO 48
#define ONE 49
#define LETTER_a 97
#define LETTER_z 122
#define LETTER_x 120
#define FULL_STOP 46

const double PI = 3.141592653589793238462643;

typedef std::function<double(double)> func_dd;

namespace functions
{
func_dd id = [](double x) { return x; };

func_dd exp = [](double x) { return std::exp(x); };
func_dd log = [](double x) { return std::log(x); };

func_dd cos = [](double x) { return std::cos(x); };
func_dd sin = [](double x) { return std::sin(x); };
func_dd tan = [](double x) { return std::tan(x); };

func_dd cosh = [](double x) { return 0.5 * (std::exp(x) + std::exp(-x)); };
func_dd sinh = [](double x) { return 0.5 * (std::exp(x) - std::exp(-x)); };
func_dd tanh = [](double x) { return sinh(x) / cosh(x); };
}

inline std::string isolateInner(std::string s)
{
	uint16_t start;
	uint16_t end;

	for (size_t i = s.length(); i != 0; i--)
	{
		char current = s[i - 1];
		if (current == ')')
			end = i - 1;

		if (current == '(')
			start = i - 1;
	}

	return s.substr(start, end - start + 1);
}

inline std::string isolateOuter(std::string s)
{
	uint16_t end;

	for (size_t i = s.length(); i != 0; i--)
	{
		char current = s[i - 1];

		if (current == '(')
			end = i - 1;
	}

	return s.substr(0, end + 1);
}
/*
inline func_dd compose(func_dd f, func_dd g)
{
	// compose et retourne la composition
}
*/
inline func_dd fromString(std::string input)
{
	// provide function string as ax

	func_dd f;
	std::string buffer = "";
	double numBuffer = 0;
	bool inDecimals = false;
	uint decimalDepth = 1;

	for (size_t i = 0; i < input.length() - 1; i++)
	{
		char c = input[i];
		if (c >= 48 && c <= 57)
		{
			if (inDecimals)
			{
				numBuffer += std::pow(10, -decimalDepth) * (c - ZERO);
				decimalDepth++;
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

	}
	return [numBuffer](double x) {
		return numBuffer * x;
	};
}

int main()
{
	std::string func_string = "1.1x";

	func_dd twentyX = fromString(func_string);
	std::cout << twentyX(0) << std::endl;
	std::cout << twentyX(1) << std::endl;
	std::cout << twentyX(2) << std::endl;
	return 0;
}