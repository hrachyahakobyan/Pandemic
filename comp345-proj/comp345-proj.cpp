// comp345-proj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "Role.h"
#include "Move.h"

PlayerIndex addPlayer(pan::Roles role, pan::Game& g, const std::string& name)
{
	using pan::Roles;
	if (role == Roles::CPlanner) return g.addPlayer<Roles::Dispatcher>(name);
	if (role == Roles::Dispatcher) return g.addPlayer<Roles::Dispatcher>(name);
	if (role == Roles::FOperative) return g.addPlayer<Roles::FOperative>(name);
	if (role == Roles::Generalist) return g.addPlayer<Roles::Generalist>(name);
	if (role == Roles::Medic) return g.addPlayer<Roles::Medic>(name);
	if (role == Roles::QSpecialist) return g.addPlayer<Roles::QSpecialist>(name);
	return g.addPlayer<Roles::Researcher>(name);
}

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace pan;
	std::cout << "Welcome to pandemic" << std::endl;
	std::cout << "Enter your name: ";
	std::string name1;
	std::cin >> name1;
	std::cout << "Enter the name of the second player: ";
	std::string name2;
	std::cin >> name2;
	srand(time(NULL));
	unsigned int role1i = (rand() % (int)(7));
	unsigned int role2i = (rand() % (int)(7));
	if (role2i == role1i){
		role2i = (role2i + 1) % 7;
	}
	auto role1 = static_cast<Roles>(role1i);
	auto role2 = static_cast<Roles>(role2i);
	std::cout << name1 << " will play as a " << RolesDescriptions.at(role1) << std::endl;
	std::cout << name2 << " will play as a " << RolesDescriptions.at(role2) << std::endl;
	Game game(Settings::Beginner(2), Map::pandemicMap());
	auto p1 = addPlayer(role1, game, name1);
	auto p2 = addPlayer(role2, game, name2);
	game.initialize();

	Move m(p1, 2);
	game.addAction(m);
	game.execute();

	std::cout << game.description() << std::endl;

	return 0;
}

