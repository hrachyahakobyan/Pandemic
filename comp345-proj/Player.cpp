#include "stdafx.h"
#include "Player.h"

namespace pan{
	std::shared_ptr<PlayerBase> player(Roles role, const std::string& name)
	{
		switch (role)
		{
		case pan::Roles::Medic:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Medic>(name));
			break;
		case pan::Roles::Dispatcher:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Dispatcher>(name));
			break;
		case pan::Roles::Generalist:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Generalist>(name));
			break;
		case pan::Roles::Researcher:
			return std::shared_ptr<PlayerBase>(new Player<Roles::Researcher>(name));
			break;
		case pan::Roles::QSpecialist:
			return std::shared_ptr<PlayerBase>(new Player<Roles::QSpecialist>(name));
			break;
		case pan::Roles::FOperative:
			return std::shared_ptr<PlayerBase>(new Player<Roles::FOperative>(name));
			break;
		case pan::Roles::CPlanner:
			return std::shared_ptr<PlayerBase>(new Player<Roles::CPlanner>(name));
			break;
		default:
			break;
		}
		return nullptr;
	}
}