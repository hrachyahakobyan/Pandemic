#include "stdafx.h"
#include "Move.h"

namespace pan{
	Move::Move() :
		ActionImpl(ActionType::Move)
	{
	}

	Move::Move(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::Move),
	player(player), targetCity(city)
	{
	}
}