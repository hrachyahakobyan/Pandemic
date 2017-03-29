#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Entity of epidemic action
	*	@author Hrachya Hakobyan
	*/
	class Epidemic : public ActionImpl<Epidemic, ActionBase>
	{
	public:
		Epidemic();
	};
}

