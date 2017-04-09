#include "stdafx.h"
#include "DirectFlight.h"


namespace pan{
	DirectFlight::DirectFlight() :
	ActionImpl(ActionType::DirectFlight){

	}

	DirectFlight::DirectFlight(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::DirectFlight),
	player(player), 
	targetCity(city)
	{
	}

	std::string DirectFlight::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player) + "\nTarget city: " + std::to_string(targetCity);
	}
}
