#include "stdafx.h"
#include "DiscardCard.h"


namespace pan{
	DiscardCard::DiscardCard(PlayerIndex player, unsigned int index) :
		player(player), index(index)
	{
	}

	ActionBase* DiscardCard::clone() const
	{
		return new DiscardCard(*this);
	}
}
