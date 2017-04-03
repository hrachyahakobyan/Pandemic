#include "stdafx.h"
#include "TreatDisease.h"

namespace pan{
	TreatDisease::TreatDisease(PlayerIndex player, DiseaseType dType) :
	ActionImpl(ActionType::TreatDisease),
	player(player), diseaseType(dType)
	{
	}
}
