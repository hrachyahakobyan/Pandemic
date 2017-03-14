#include "stdafx.h"
#include "BuildResearchStation.h"

namespace pan{
	BuildResearchStation::BuildResearchStation(PlayerIndex player) :
		player(player)
	{
	}

	ActionBase* BuildResearchStation::clone() const
	{
		return new BuildResearchStation(*this);
	}
}
