#include "stdafx.h"
#include "AirliftAction.h"

namespace pan{
	AirliftAction::AirliftAction() :
		ActionImpl(ActionType::Airlift)
	{
	}

	AirliftAction::AirliftAction(PlayerIndex player, PlayerIndex target, CityIndex city) :
		ActionImpl(ActionType::Airlift),
		player(player), target(target), city(city)
	{
	}
}