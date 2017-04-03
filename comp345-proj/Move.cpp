#include "stdafx.h"
#include "Move.h"

namespace pan{
	Move::Move(PlayerIndex player, CityIndex city) :
	ActionImpl(ActionType::Move),
	player(player), targetCity(city)
	{
	}
}