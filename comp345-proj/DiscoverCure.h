#pragma once
#include "ActionBase.h"
#include "common.h"

namespace pan{
	/**
	*	@brief Class representing a discover cure action
	*	@author Hrachya Hakobyan
	*/
	class DiscoverCure : public ActionImpl<DiscoverCure, ActionBase>{
	public:
		DiscoverCure(PlayerIndex player, DiseaseType dType);
		PlayerIndex player;
		DiseaseType diseaseType;
		ActionBase* clone() const;
	};
}