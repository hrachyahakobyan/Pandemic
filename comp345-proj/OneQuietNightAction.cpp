#include "stdafx.h"
#include "OneQuietNightAction.h"

namespace pan{
	OneQuietNightAction::OneQuietNightAction() :
		ActionImpl(ActionType::OneQuietNight)
	{
	}

	OneQuietNightAction::OneQuietNightAction(PlayerIndex player) :
		ActionImpl(ActionType::OneQuietNight),
		player(player)
	{
	}

	std::string OneQuietNightAction::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player);
	}
}