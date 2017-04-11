#include "stdafx.h"
#include "Pandemic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	using namespace pan;
	Settings s(2, 4, 4);
	s.discoverCureCardCount = 1;
	s.playerDrawCount = 4;
	pan::Game game(s, pan::Map::pandemicMap());
	game.addRandomPlayer("Player 1");
	game.addRandomPlayer("Player 2");
	game.initialize();
	Pandemic w;
	w.show();
	w.start();
	return a.exec();
}
