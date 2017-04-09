#include "stdafx.h"
#include "DiscoverCure.h"

namespace pan{
	DiscoverCure::DiscoverCure() :
		ActionImpl(ActionType::DiscoverCure){
	}

	DiscoverCure::DiscoverCure(PlayerIndex player, DiseaseType dType) :
	ActionImpl(ActionType::DiscoverCure),
	player(player), diseaseType(dType)
	{
	}

	std::string DiscoverCure::description() const
	{
		return ActionBase::description() + "\nPlayer: " + std::to_string(player) + "\nDisease type: " + std::to_string(diseaseType);
	}
}
