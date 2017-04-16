#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Encapsulates the parameters of GovGrant event action
	*	@author Hrachya Hakobyan
	*/
	class GovGrantAction : public ActionImpl<GovGrantAction, ActionBase>
	{
	public:
		GovGrantAction();
		GovGrantAction(pan::PlayerIndex player, pan::CityIndex index);
		/**
		*	The initiating player
		*/
		PlayerIndex player;
		/**
		*	The city to build a research station in
		*/
		CityIndex city;
	};
}

