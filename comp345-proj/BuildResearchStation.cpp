#include "stdafx.h"
#include "BuildResearchStation.h"

namespace pan{
	BuildResearchStation::BuildResearchStation(PlayerIndex player) :
	ActionImpl(ActionType::BuildStation),
	player(player)
	{
	}
}
