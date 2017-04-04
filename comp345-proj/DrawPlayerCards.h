#pragma once
#include "ActionBase.h"


namespace pan{
	/**
	*	@brief Class representing the action of a player drawing player cards
	*	@author Hrachya Hakobyan
	*/
	class DrawPlayerCards : public ActionImpl<DrawPlayerCards, ActionBase>{
	public:
		DrawPlayerCards();
		DrawPlayerCards(PlayerIndex player);
		PlayerIndex player;
	};
}