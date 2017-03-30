#include "stdafx.h"
#include "Pandemic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Pandemic w;
	w.show();
	pan::Game game(pan::Settings::Beginner(2), pan::Map::pandemicMap());
	game.addRandomPlayer("Player 1");
	game.addRandomPlayer("Player 2");
	game.initialize();
	w.update(std::move(game));
	return a.exec();
}
