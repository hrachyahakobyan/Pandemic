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
		PlayerIndex initiater;
		PlayerIndex targetPlayer;
		Map::CityIndex targetCity;
	};
}