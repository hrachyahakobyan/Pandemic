#include "stdafx.h"
#include "GovGrantAction.h"


namespace pan{
	GovGrantAction::GovGrantAction() :
	ActionImpl(ActionType::GovGrant)
	{
	}

	GovGrantAction::GovGrantAction(PlayerIndex player, CityIndex city) :
		ActionImpl(ActionType::GovGrant),
		player(player), city(city)
	{
	}
}