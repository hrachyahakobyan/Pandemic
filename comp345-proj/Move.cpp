#include "stdafx.h"
#include "Move.h"

namespace pan{
	Move::Move(PlayerIndex player, CityIndex city) :
		player(player), targetCity(city)
	{
	}
}