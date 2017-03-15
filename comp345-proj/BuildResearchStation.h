#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Class representing a build research station action.
	*	@author Hrachya Hakobyan
	*/
	class BuildResearchStation : public ActionImpl<BuildResearchStation, ActionBase>{
	public:
		BuildResearchStation(PlayerIndex player);
		PlayerIndex player;
	};
}