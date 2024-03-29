#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing the infect action initiated by the player.
	*	Note it is different from the Infect action as it does not take any
	*	parameters besides the initiatin player's index.
	*	@author Hrachya Hakobyan
	*/
	class PlayerInfect : public ActionImpl<PlayerInfect, ActionBase>{
	public:
		PlayerInfect();
		PlayerInfect(PlayerIndex player);
		PlayerIndex player;

		std::string description() const;
	};
}