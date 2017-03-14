#include "stdafx.h"
#include "DirectFlight.h"


namespace pan{
	DirectFlight::DirectFlight(PlayerIndex player, Map::CityIndex city) :
		player(player), targetCity(city)
	{
	}

	ActionBase* DirectFlight::clone() const
	{
		return new DirectFlight(*this);
	}
}
