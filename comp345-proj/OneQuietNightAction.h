#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing a driver/ferry action.
	*	@author Hrachya Hakobyan
	*/
	class OneQuietNightAction : public ActionImpl<OneQuietNightAction, ActionBase>{
	public:
		OneQuietNightAction();
		OneQuietNightAction(PlayerIndex player);
		PlayerIndex player;
		std::string description() const;
	};
}