#include "stdafx.h"
#include "TreatDisease.h"

namespace pan{
	TreatDisease::TreatDisease(PlayerIndex player, DiseaseType dType) :
	ActionImpl(ActionType::Regular),
	player(player), diseaseType(dType)
	{
	}
}
