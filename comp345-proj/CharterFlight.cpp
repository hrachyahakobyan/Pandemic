#include "stdafx.h"
#include "CharterFlight.h"

namespace pan{
	CharterFlight::CharterFlight(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::Regular),
	player(player),
	targetCity(city)
	{
	}
}
