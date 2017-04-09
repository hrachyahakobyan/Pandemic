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

	std::string ShareKnowledge::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player) + "\nTarget: " + std::to_string(target) + "\nCard index: " + std::to_string(cardIndex);
	}
}

