#include "stdafx.h"
#include "CharterFlight.h"

namespace pan{
	CharterFlight::CharterFlight() :
		ActionImpl(ActionType::CharterFlight)
	{
	}

	CharterFlight::CharterFlight(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::CharterFlight),
	player(player),
	targetCity(city)
	{
	}
}
