#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing a driver/ferry action.
	*	@author Hrachya Hakobyan
	*/
	class Move : public ActionImpl<Move, ActionBase>{
	public:
		Move();
		Move(PlayerIndex player, CityIndex city);
		PlayerIndex player;
		CityIndex targetCity;
	};
}