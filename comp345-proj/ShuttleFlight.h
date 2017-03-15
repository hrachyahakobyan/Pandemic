#pragma once
#include "ActionBase.h"
#include "Map.h"
#include "common.h"

namespace pan{
	/**
	*	@brief Class representing a shuttle flight action
	*	@author Hrachya Hakobyan
	*/
	class ShuttleFlight : public ActionImpl<ShuttleFlight, ActionBase>{
	public:
		ShuttleFlight(PlayerIndex player, Map::CityIndex city);
		PlayerIndex player;
		Map::CityIndex targetCity;
		ActionBase* clone() const;
	};
}