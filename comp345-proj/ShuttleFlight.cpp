#include "stdafx.h"
#include "ShuttleFlight.h"

namespace pan{
	ShuttleFlight::ShuttleFlight(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::ShuttleFlight),
	player(player), targetCity(city)
	{
	}
}
