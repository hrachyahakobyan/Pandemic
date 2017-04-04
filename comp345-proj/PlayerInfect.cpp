#include "stdafx.h"
#include "PlayerInfect.h"


namespace pan{
	PlayerInfect::PlayerInfect() :
	ActionImpl(ActionType::Infect)
	{
	}

	PlayerInfect::PlayerInfect(PlayerIndex player) :
	ActionImpl(ActionType::Infect),
	player(player)
	{
	}
}
