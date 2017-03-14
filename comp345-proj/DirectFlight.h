#pragma once
#include "ActionBase.h"
#include "Map.h"
#include "common.h"

namespace pan{
	/**
	*	@brief Class representing a direct flight action
	*	@author Hrachya Hakobyan
	*/
	class DirectFlight : public ActionImpl<DirectFlight, ActionBase>{
	public:
		DirectFlight(PlayerIndex player, Map::CityIndex city);
		PlayerIndex player;
		Map::CityIndex targetCity;
		ActionBase* clone() const;
	};
}