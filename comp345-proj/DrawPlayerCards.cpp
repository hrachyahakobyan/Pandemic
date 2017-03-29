#include "stdafx.h"
#include "DrawPlayerCards.h"

namespace pan{
	DrawPlayerCards::DrawPlayerCards(PlayerIndex player) :
	ActionImpl(ActionType::Draw),
	player(player)
	{
	}
}
