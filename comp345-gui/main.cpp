#include "stdafx.h"
#include "Pandemic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pan::Game game(pan::Settings::Beginner(2), pan::Map::pandemicMap());
	game.addRandomPlayer("Player 1");
	game.addRandomPlayer("Player 2");
	game.initialize();
	Pandemic w(std::move(game));
	w.show();
	return a.exec();
}
