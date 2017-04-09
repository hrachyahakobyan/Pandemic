#include "stdafx.h"
#include "DrawPlayerCards.h"

namespace pan{
	DrawPlayerCards::DrawPlayerCards() :
	ActionImpl(ActionType::Draw)
	{
	}

	DrawPlayerCards::DrawPlayerCards(PlayerIndex player) :
	ActionImpl(ActionType::Draw),
	player(player)
	{
	}

	std::string DrawPlayerCards::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player);
	}
}
