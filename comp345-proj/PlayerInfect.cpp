#include "stdafx.h"
#include "PlayerInfect.h"


namespace pan{
	PlayerInfect::PlayerInfect() :
	ActionImpl(ActionType::Infect)
	{
	}

	PlayerInfect::PlayerInfect(PlayerIndex player) :
	ActionImpl(ActionType::Infect),
	player(player)
	{
	}

	std::string PlayerInfect::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player);
	}
}
