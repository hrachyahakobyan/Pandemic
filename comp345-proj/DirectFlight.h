#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing a direct flight action
	*	@author Hrachya Hakobyan
	*/
	class DirectFlight : public ActionImpl<DirectFlight, ActionBase>{
	public:
		DirectFlight();
		DirectFlight(PlayerIndex player, CityIndex city);
		PlayerIndex player;
		CityIndex targetCity;

		std::string description() const;
	};
}