#include "stdafx.h"
#include "DiscoverCure.h"

namespace pan{
	DiscoverCure::DiscoverCure(PlayerIndex player, DiseaseType dType) :
		player(player), diseaseType(dType)
	{
	}

	ActionBase* DiscoverCure::clone() const
	{
		return new DiscoverCure(*this);
	}
}
