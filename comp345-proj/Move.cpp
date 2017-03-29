#include "stdafx.h"
#include "Move.h"

namespace pan{
	Move::Move(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::Regular),
	player(player), targetCity(city)
	{
	}
}