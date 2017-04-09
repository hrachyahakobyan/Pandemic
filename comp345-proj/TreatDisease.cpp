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

	std::string TreatDisease::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player) + "\nDisease type: " + std::to_string(diseaseType);
	}
}
