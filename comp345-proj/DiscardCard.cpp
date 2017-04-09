#include "stdafx.h"
#include "DiscardCard.h"


namespace pan{
	DiscardCard::DiscardCard() :
		ActionImpl(ActionType::Discard){

	}

	DiscardCard::DiscardCard(PlayerIndex player, unsigned int index) :
	ActionImpl(ActionType::Discard),
	player(player), index(index)
	{
	}

	std::string DiscardCard::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player) + "\nCard index: " + std::to_string(index);
	}
}
