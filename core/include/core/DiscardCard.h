#pragma once
#include "ActionBase.h"


namespace pan{
	/**
	*	@brief Class representing the action of a player discarding a card.
	*	@author Hrachya Hakobyan
	*/
	class DiscardCard : public ActionImpl<DiscardCard, ActionBase>{
	public:
		DiscardCard();
		DiscardCard(PlayerIndex player, unsigned int index);
		PlayerIndex player;
		unsigned int index;
	};
}