#include "stdafx.h"
#include "ShareKnowledge.h"

namespace pan{
	ShareKnowledge::ShareKnowledge(PlayerIndex player, PlayerIndex target, int cardIndex) :
	ActionImpl(ActionType::Regular),
	player(player), target(target), cardIndex(cardIndex){
		PlayerIndex player;
		PlayerIndex target;
		int cardIndex;
	}
}

