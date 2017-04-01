#include "stdafx.h"
#include "Player.h"

namespace pan{
	std::shared_ptr<PlayerBase> player(Roles role, PlayerIndex index, const std::string& name)
	{
		switch (role)
		{
		case pan::Roles::Medic:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Medic>(index, name));
			break;
		case pan::Roles::Dispatcher:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Dispatcher>(index, name));
			break;
		case pan::Roles::Scientist:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Scientist>(index, name));
			break;
		case pan::Roles::Researcher:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Researcher>(index, name));
			break;
		case pan::Roles::QSpecialist:
			return std::shared_ptr<PlayerBase>(new Player<Roles::QSpecialist>(index, name));
			break;
		case pan::Roles::OperationsExpert:
			return std::shared_ptr<PlayerBase>(new Player<Roles::OperationsExpert>(index, name));
			break;
		case pan::Roles::CPlanner:
			return std::shared_ptr<PlayerBase>(new Player<Roles::CPlanner>(index, name));
			break;
		default:
			break;
		}
		return nullptr;
	}
}