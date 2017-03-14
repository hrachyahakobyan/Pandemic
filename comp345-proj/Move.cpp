#include "stdafx.h"
#include "Move.h"

namespace pan{
	Move::Move(PlayerIndex player, Map::CityIndex city) :
		player(player), targetCity(city)
	{
	}

	ActionBase* Move::clone() const
	{
		return new Move(*this);
	}
}