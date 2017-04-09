#include "stdafx.h"
#include "BuildResearchStation.h"

namespace pan{
	BuildResearchStation::BuildResearchStation() :
	ActionImpl(ActionType::BuildStation)
	{
	}

	BuildResearchStation::BuildResearchStation(PlayerIndex player) :
	ActionImpl(ActionType::BuildStation),
	player(player)
	{
	}

	std::string BuildResearchStation::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player);
	}
}
