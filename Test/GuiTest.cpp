#include "stdafx.h"
#include "GuiTest.h"

pan::GuiTest::GuiTest()
{	
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Pandemic" /*, sf::Style::Fullscreen*/ );
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
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Q:
					window.close();
					break;
				}


			case sf::Event::MouseButtonPressed:
				std::cout << "mouse button pressed" << std::endl;
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					std::cout << "left mouse button pressed" << std::endl;
				}

			}

		}


		window.clear();
		window.display();
	}
}