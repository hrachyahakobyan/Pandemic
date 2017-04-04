#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing a direct flight action
	*	@author Hrachya Hakobyan
	*/
	class ShareKnowledge : public ActionImpl<ShareKnowledge, ActionBase>{
	public:
		ShareKnowledge();
		ShareKnowledge(PlayerIndex player, PlayerIndex target, int cardIndex);
		PlayerIndex player;
		PlayerIndex target;
		int cardIndex;
	};
}