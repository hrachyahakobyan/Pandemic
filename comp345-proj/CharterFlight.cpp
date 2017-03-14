#include "stdafx.h"
#include "CharterFlight.h"

namespace pan{
	CharterFlight::CharterFlight(PlayerIndex player, Map::CityIndex city) :
		player(player), targetCity(city)
	{
	}

	ActionBase* CharterFlight::clone() const
	{
		return new CharterFlight(*this);
	}
}
