// comp345-proj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EventCard.h"
#include "InfectionCard.h"
#include "PlayerCard.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace pan;
	PlayerCard pc(0);
	InfectionCard ic;
	EventCard ec(EventType::DummyEvent);
	std::cout << pc.description() << std::endl;
	std::cout << ic.description() << std::endl;
	std::cout << ec.description() << std::endl;
	return 0;
}

