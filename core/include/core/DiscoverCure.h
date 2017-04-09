#pragma once
#include "ActionBase.h"


namespace pan{
	/**
	*	@brief Class representing a discover cure action
	*	@author Hrachya Hakobyan
	*/
	class DiscoverCure : public ActionImpl<DiscoverCure, ActionBase>{
	public:
		DiscoverCure();
		DiscoverCure(PlayerIndex player, DiseaseType dType);
		PlayerIndex player;
		DiseaseType diseaseType;

		std::string description() const;
	};
}