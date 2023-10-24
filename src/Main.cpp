////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fourier.hpp>
#include <function_window.hpp>
#include <input_handler.hpp>
#include <windows.h>
#include <guiwindow.hpp>
#include <fnbox.hpp>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Create the window of the application
	constexpr int window_width = 1920;
	constexpr int window_height = 980;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 1;
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Fourier Series Visualisator", sf::Style::Default, settings);
	const uint32_t framerate = 120;
	window.setFramerateLimit(framerate);
	window.setKeyRepeatEnabled(true);
	window.setMouseCursorGrabbed(false);
	window.setMouseCursorVisible(true);

	sf::Font font;

	if (!font.loadFromFile("content/Pica.ttf"))
	{
		std::cout << "Failed to load...\n";
	};

	// FourierSeries series({ 1, 3, 5 }, {});
	// Polynomial p({0, 0, 1});

	GraphWindow fwin({ 0, 0 }, { 1920, 600 }, { -10, 10 }, { -10, 10 });


	InputBox box(fwin, { 0, 650 });
	box.setFont(font);

	GuiWindow gWindow({0, 0},{1920, 880}, fwin);
	gWindow.setFont(font);

	//FnBox fbox(fwin, {1450, 0});
	//fbox.setFont(font);

	gWindow.addFunction(SumFunction(Polynomial({0, 1}),FourierSeries({1},{})));

	gWindow.addFunction(SumFunction(Polynomial({0, 1}),FourierSeries({},{1})));




	/*
	box.inputLogic(P_KEY);
	box.inputLogic(49);
	box.inputLogic(SPACE_KEY);
	box.inputLogic(50);
	box.inputLogic(ENTER_KEY);
	box.inputLogic(51);
	box.inputLogic(ENTER_KEY);
	*/

	// fwin.addFunction(series);

	// Main loop

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::TextEntered:
					box.typing(event);
					break;
				case sf::Event::MouseButtonPressed:
					if(gWindow.isInClearBtn(window))
						gWindow.clear();
					if(gWindow.isInDelBtn(window))
						gWindow.deleteFunction();
				default:
					break;
			}
		};

		window.clear(sf::Color::Black);
		gWindow.drawTo(window);
		box.drawTo(window);
		//fbox.drawTo(window);
		window.display();
	}

	return 0;
}