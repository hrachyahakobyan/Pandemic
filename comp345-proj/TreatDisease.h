#pragma once
#include "ActionBase.h"


namespace pan{
	/**
	*	@brief Class representing a treat disease action
	*	@author Hrachya Hakobyan
	*/
	class TreatDisease : public ActionImpl<TreatDisease, ActionBase>{
	public:
		TreatDisease(PlayerIndex player, DiseaseType dType);
		PlayerIndex player;
		DiseaseType diseaseType;
	};
}