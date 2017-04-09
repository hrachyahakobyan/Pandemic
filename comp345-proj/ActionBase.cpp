#include "stdafx.h"
#include "ActionBase.h"

namespace pan{

	bool isRegular(ActionType type)
	{
		return (type == ActionType::Move ||
			type == ActionType::CharterFlight ||
			type == ActionType::DirectFlight ||
			type == ActionType::ShuttleFlight ||
			type == ActionType::BuildStation ||
			type == ActionType::TreatDisease ||
			type == ActionType::ShareKnowledge ||
			type == ActionType::DiscoverCure);
	}

	bool ActionBase::isRegularAction() const
	{
		return isRegular(type);
	}

	std::string ActionBase::description() const
	{
		return ActionTypeDescriptions.at(type);
	}
}