#include "stdafx.h"
#include "PlayerInfect.h"


namespace pan{
	PlayerInfect::PlayerInfect(PlayerIndex player) :
	ActionImpl(ActionType::Infect),
	player(player)
	{
	}
}
