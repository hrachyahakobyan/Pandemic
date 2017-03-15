#include "stdafx.h"
#include "ShuttleFlight.h"

namespace pan{
	ShuttleFlight::ShuttleFlight(PlayerIndex player, Map::CityIndex city) :
		player(player), targetCity(city)
	{
	}
}
