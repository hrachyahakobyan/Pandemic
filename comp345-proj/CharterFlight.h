#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing a charter flight action
	*	@author Hrachya Hakobyan
	*/
	class CharterFlight : public ActionImpl<CharterFlight, ActionBase>{
	public:
		CharterFlight(PlayerIndex player, CityIndex city);
		PlayerIndex player;
		CityIndex targetCity;
	};
}