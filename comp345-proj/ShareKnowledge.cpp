#include "stdafx.h"
#include "ShareKnowledge.h"

namespace pan{
	ShareKnowledge::ShareKnowledge() :
		ActionImpl(ActionType::ShareKnowledge){
	}

	ShareKnowledge::ShareKnowledge(PlayerIndex player, PlayerIndex target, int cardIndex) :
	ActionImpl(ActionType::ShareKnowledge),
	player(player), target(target), cardIndex(cardIndex){
	}
}

