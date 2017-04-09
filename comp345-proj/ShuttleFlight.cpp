#include "stdafx.h"
#include "ShuttleFlight.h"

namespace pan{
	ShuttleFlight::ShuttleFlight() :
		ActionImpl(ActionType::ShuttleFlight)
	{
	}

	ShuttleFlight::ShuttleFlight(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::ShuttleFlight),
	player(player), targetCity(city)
	{
	}

	std::string ShuttleFlight::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player) + "\nTarget city: " + std::to_string(targetCity);
	}
}
