#include "stdafx.h"
#include "DirectFlight.h"


namespace pan{
	DirectFlight::DirectFlight(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::DirectFlight),
	player(player), 
	targetCity(city)
	{
	}
}
