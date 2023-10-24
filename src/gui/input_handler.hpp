#pragma once

#include <functions/composite_function.hpp>

#include <gui/function_window.hpp>
#include <gui/gui_elements/textbox.hpp>

#define P_KEY 80
#define C_KEY 67
#define F_KEY 70

#define SPACE_KEY 32
#define PLUS_KEY 43
#define MINUS_KEY 45
#define TIMES_KEY 42

#define POINT_KEY 46

enum typingMode
{
	def,
	polynomial,
	fourier
};

enum fourierMode
{
	sine,
	cosine
};

inline int digits_after_decimal_point(float x)
{
	int i;
	for (i = 0; x != rint(x); x += x, i++)
		;
	return i;
}

class InputBox : public Textbox
{
public:
	InputBox()
	{}

	InputBox(GraphWindow& window) :
		fWindow { &window }
	{}

	InputBox(GraphWindow& window, sf::Vector2f position) :
		fWindow { &window }
	{
		setCharacterSize(30);
		setSelected(false);
		setPosition(position);
	}

	void typing(sf::Event input)
	{
		int charTyped = input.text.unicode;

		if (charTyped == C_KEY)
		{
			fWindow->clear();
			tmode = def;
			fmode = sine;
			numberBuffer = 0;
			setText("");
			coeffBuffer.clear();
			sineBuffer.clear();
			return;
		}

		if (charTyped == DELETE_KEY && hasLimit && string.str().length() >= characterLimit)
		{
			deleteLastCharacter();
			text.setString(string.str() + "_");
			return;
		}
		inputLogic(charTyped);
	}

	void drawTo(sf::RenderWindow& window)
	{
		Textbox::drawTo(window);
	}

	void setFont(sf::Font& font)
	{
		Textbox::setFont(font);
	}

	bool getSelected()
	{
		return isSelected;
	}

private:
	GraphWindow* fWindow = nullptr;
	bool isSelected = false;

	typingMode tmode = def;
	fourierMode fmode = sine;
	bool isAddingModeOn = false;
	bool isMultiplyModeOn = false;

	std::vector<float> coeffBuffer;
	std::vector<float> sineBuffer;
	std::vector<float> polyBuffer;
	float numberBuffer = 0;

	void deleteLastCharacter()
	{
		numberBuffer = deleteLastDigit(numberBuffer);
		Textbox::deleteLastCharacter();
	}

	void polynomialInputLogic(int charTyped)
	{
		if (charTyped == ESCAPE_KEY)
		{
			tmode = def;
			return;
		}

		if (charTyped >= 48 && charTyped < 58)
		{
			numberBuffer = numberBuffer * 10 + charTyped - 48;
		}

		if (charTyped == ENTER_KEY)
		{

			coeffBuffer.push_back(numberBuffer);
			tmode = def;

			if (isAddingModeOn || isMultiplyModeOn)
			{
				polyBuffer = coeffBuffer;
				tmode = fourier;
			}
			else
				fWindow->addFunction(Polynomial(coeffBuffer));

			coeffBuffer.clear();
			numberBuffer = 0;
			string.str("");
			text.setString("_");
			return;
		}

		if (charTyped == SPACE_KEY)
		{
			coeffBuffer.push_back(numberBuffer);
			numberBuffer = 0;
		}
		Textbox::inputLogic(charTyped);
	}

	void fourierInputLogic(int charTyped)
	{
		if (charTyped == ESCAPE_KEY)
		{
			tmode = def;
			numberBuffer = 0;
			sineBuffer.clear();
			coeffBuffer.clear();
			isAddingModeOn = false;
			isMultiplyModeOn = false;
			return;
		}

		if (charTyped >= 48 && charTyped < 58)
		{
			numberBuffer = numberBuffer * 10 + charTyped - 48;
		}

		if (charTyped == ENTER_KEY)
		{
			coeffBuffer.push_back(numberBuffer);
			numberBuffer = 0;
			switch (fmode)
			{
				case sine:
					fmode = cosine;
					sineBuffer = coeffBuffer;
					coeffBuffer.clear();
					break;

				case cosine: {
					fmode = sine;
					tmode = def;
					FourierSeries newSeries(sineBuffer, coeffBuffer);
					if (isAddingModeOn)
					{
						fWindow->drawSum(newSeries, Polynomial(polyBuffer));
						isAddingModeOn = false;
					}
					else if (isMultiplyModeOn)
					{
						fWindow->drawProduct(newSeries, Polynomial(polyBuffer));
						isMultiplyModeOn = false;
					}
					else
						fWindow->addFunction(newSeries);
					sineBuffer.clear();
					coeffBuffer.clear();
					break;
				}
				default:
					break;
			}

			string.str("");
			text.setString("_");
			return;
		}

		if (charTyped == SPACE_KEY)
		{
			coeffBuffer.push_back(numberBuffer);
			numberBuffer = 0;
		}

		Textbox::inputLogic(charTyped);
	}

	void defaultInputLogic(int charTyped)
	{
		if (charTyped == ESCAPE_KEY)
		{
			setSelected(false);
			return;
		}

		if (charTyped == P_KEY)
		{
			tmode = polynomial;
			return;
		}

		if (charTyped == F_KEY)
		{
			tmode = fourier;
			return;
		}

		if (charTyped == PLUS_KEY)
		{
			isAddingModeOn = true;
			tmode = polynomial;
			return;
		}

		if (charTyped == TIMES_KEY)
		{
			isMultiplyModeOn = true;
			tmode = polynomial;
			return;
		}

		return;
	}

	void inputLogic(int charTyped)
	{
		switch (tmode)
		{
			case def:
				defaultInputLogic(charTyped);
				break;

			case polynomial:
				polynomialInputLogic(charTyped);
				break;

			case fourier:
				fourierInputLogic(charTyped);
				break;
			default:
				break;
		}
	}

	float deleteLastDigit(float x)
	{
		float residue = x - std::floor(x);

		if (residue < pow(10, -4))
		{
			return (x - (int)x % 10) / 10;
		}

		int nbDigitsAfterPoint = digits_after_decimal_point(x);

		return (x * pow(10, nbDigitsAfterPoint) - (int)(x * pow(10, nbDigitsAfterPoint)) % 10) / pow(10, nbDigitsAfterPoint);
	}
};