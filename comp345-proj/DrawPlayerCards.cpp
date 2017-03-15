#include "stdafx.h"
#include "DrawPlayerCards.h"

namespace pan{
	DrawPlayerCards::DrawPlayerCards(PlayerIndex player) :
		player(player)
	{
	}

	ActionBase* DrawPlayerCards::clone() const
	{
		return new DrawPlayerCards(*this);
	}
}
