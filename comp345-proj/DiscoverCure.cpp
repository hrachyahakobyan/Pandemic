#include "stdafx.h"
#include "DiscoverCure.h"

namespace pan{
	DiscoverCure::DiscoverCure(PlayerIndex player, DiseaseType dType) :
	ActionImpl(ActionType::Regular),
	player(player), diseaseType(dType)
	{
	}
}
