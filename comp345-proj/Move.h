#pragma once
#include "ActionBase.h"
#include "Map.h"
#include "common.h"

namespace pan{
	/**
	*	@brief Class representing a driver/ferry action.
	*	@author Hrachya Hakobyan
	*/
	class Move : public ActionImpl<Move, ActionBase>{
	public:
		Move(PlayerIndex player, Map::CityIndex city);
		PlayerIndex player;
		Map::CityIndex targetCity;
	};
}