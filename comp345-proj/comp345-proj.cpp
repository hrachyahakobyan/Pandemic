// comp345-proj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MapView.h"
#include "Pawn.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace gui;
	sf::RenderWindow window(sf::VideoMode(16 * 100, 9 * 100), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	gui::MapView map;
	float scale = 1600.0f / 3840;
	map.setScale({ scale, scale });
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(map);
		window.display();
	}
	return 0;
}

