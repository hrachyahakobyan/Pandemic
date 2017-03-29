#include "stdafx.h"
#include "ShuttleFlight.h"

namespace pan{
	ShuttleFlight::ShuttleFlight(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::Regular),
	player(player), targetCity(city)
	{
	}
}
