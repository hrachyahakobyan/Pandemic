#include "stdafx.h"
#include "TreatDisease.h"

namespace pan{
	TreatDisease::TreatDisease() :
	ActionImpl(ActionType::TreatDisease)
	{
	}

	TreatDisease::TreatDisease(PlayerIndex player, DiseaseType dType) :
	ActionImpl(ActionType::TreatDisease),
	player(player), diseaseType(dType)
	{
	}
}
