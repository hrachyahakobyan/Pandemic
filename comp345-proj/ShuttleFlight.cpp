#include "stdafx.h"
#include "ShuttleFlight.h"

namespace pan{
	ShuttleFlight::ShuttleFlight(PlayerIndex player, Map::CityIndex city) :
		player(player), targetCity(city)
	{
	}


	ActionBase* ShuttleFlight::clone() const
	{
		return new ShuttleFlight(*this);
	}
}
