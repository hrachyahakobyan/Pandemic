#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing a shuttle flight action
	*	@author Hrachya Hakobyan
	*/
	class ShuttleFlight : public ActionImpl<ShuttleFlight, ActionBase>{
	public:
		ShuttleFlight();
		ShuttleFlight(PlayerIndex player, CityIndex city);
		PlayerIndex player;
		CityIndex targetCity;

		std::string description() const;
	};
}