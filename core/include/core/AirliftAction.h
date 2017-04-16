#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Encapsulates the parameters of GovGrant event action
	*	@author Hrachya Hakobyan
	*/
	class AirliftAction : public ActionImpl<AirliftAction, ActionBase>
	{
	public:
		AirliftAction();
		AirliftAction(pan::PlayerIndex player, pan::PlayerIndex target, pan::CityIndex index);
		/**
		*	The initiating player
		*/
		PlayerIndex player;
		/**
		*	The target player
		*/
		PlayerIndex target;
		/**
		*	The city to build a research station in
		*/
		CityIndex city;
	};
}
