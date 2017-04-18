#include "stdafx.h"
#include "GovGrantAction.h"


namespace pan{
	GovGrantAction::GovGrantAction() :
	ActionImpl(ActionType::GovGrant)
	{
	}

	GovGrantAction::GovGrantAction(PlayerIndex player, CityIndex city) :
		ActionImpl(ActionType::GovGrant),
		player(player), city(city)
	{
	}

	std::string GovGrantAction::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player) + "\nTarget city: " + std::to_string(city);
	}
}