////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <windows.h>
#include <gui/fnbox.hpp>
#include <gui/input_handler_v2.hpp>
#include <gui/guiwindow.hpp>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Create the window of the application
	constexpr int window_width = 1920;
	constexpr int window_height = 980;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 1;
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Weird Lil Function Visualisator", sf::Style::Default, settings);
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


	GraphWindow fwin({ 0, 0 }, { 1920, 600 }, { -10, 10 }, { -10, 10 });


	InputBox box(fwin, { 0, 650 });
	box.setFont(font);







	// fwin.addFunction(series);

	// Main loop

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				fwin.clear();
			}

			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::TextEntered:
					box.typing(event);
					break;

				default:
					break;
			}
		};

		window.clear(sf::Color::Black);
		box.drawTo(window);
		fwin.drawTo(window);
		window.display();
	}

	return 0;
}

