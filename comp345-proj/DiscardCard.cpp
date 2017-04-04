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
}
