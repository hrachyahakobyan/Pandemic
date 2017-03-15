#pragma once
#include "ActionBase.h"
#include "Map.h"
#include "common.h"

namespace pan{
	/**
	*	@brief Class representing a charter flight action
	*	@author Hrachya Hakobyan
	*/
	class CharterFlight : public ActionImpl<CharterFlight, ActionBase>{
	public:
		CharterFlight(PlayerIndex player, Map::CityIndex city);
		PlayerIndex player;
		Map::CityIndex targetCity;
	};
}