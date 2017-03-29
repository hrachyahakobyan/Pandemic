#include "stdafx.h"
#include "BuildResearchStation.h"

namespace pan{
	BuildResearchStation::BuildResearchStation(PlayerIndex player) :
	ActionImpl(ActionType::Regular),
	player(player)
	{
	}
}
