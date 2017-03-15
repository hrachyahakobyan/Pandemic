#pragma once
#include "ActionBase.h"
#include "common.h"

namespace pan{
	/**
	*	@brief Class representing the action of a player drawing player cards
	*	@author Hrachya Hakobyan
	*/
	class DrawPlayerCards : public ActionImpl<DrawPlayerCards, ActionBase>{
	public:
		DrawPlayerCards(PlayerIndex player);
		PlayerIndex player;
		ActionBase* clone() const;
	};
}