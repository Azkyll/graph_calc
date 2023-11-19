#pragma once

#include <SFML/Audio.hpp>
#include <gui/gui_elements/button.hpp>

#define PI 3.141592

inline std::vector<sf::Int16> normalize(std::vector<float> arr, const float newMin, const float newMax)
{
	std::vector<sf::Int16> output;
	output.reserve(44100);
	const float max = *std::max_element(std::begin(arr), std::end(arr));
	const float min = *std::min_element(std::begin(arr), std::end(arr));
	const float amplitude = max - min;
	const float desired_amplitude = newMax - newMin;
	const float amplitude_ratio = desired_amplitude / amplitude;

	for (uint i = 0; i < 44100; ++i)
	{
		output.push_back(amplitude_ratio * arr[i]);
	}

	return output;
}

inline const std::vector<sf::Int16> getSample(functions::func_ff& f, const float start, const float finish)
{
	std::vector<float> temp;
	temp.reserve(44100);
	const float delta = finish - start;
	for (uint n = 0; n < 44100; ++n)
	{
		temp.push_back(f((start + delta * n / 44100) * 440));
	}
	return normalize(temp, -32767, 32767);
}

inline sf::SoundBuffer fromFunction(functions::func_ff& f)
{
	sf::SoundBuffer sb;
	std::vector<sf::Int16> samples = getSample(f, 0, 2 * PI);
	sb.loadFromSamples(&samples[0], 44100, 1, 44100);
	return sb;
}

class PlayButton : public Button
{
public:
	PlayButton()
	{
		Button();
		Button::setText("play");
		Button::setTextFillColor(sf::Color::Red);
		Button::setPosition({ 850, 850 });
		Button::setSize({ 150, 150 });
	}

	void setFunction(functions::func_ff f)
	{
		buffer = fromFunction(f);
		sound.setBuffer(buffer);
	}

	virtual void click() override
	{
		sound.play();
	}

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};