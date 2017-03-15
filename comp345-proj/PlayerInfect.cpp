#include "stdafx.h"
#include "PlayerInfect.h"


namespace pan{
	PlayerInfect::PlayerInfect(PlayerIndex player) :
		player(player)
	{
	}

	ActionBase* PlayerInfect::clone() const
	{
		return new PlayerInfect(*this);
	}
}
