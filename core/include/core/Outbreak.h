#pragma once
#include "Infect.h"

namespace pan{
	/**
	*	@brief Encapsulates the parameters of Outbreak call
	*	@author Hrachya Hakobyan
	*/
	class Outbreak : public ActionImpl<Outbreak, ActionBase>
	{
	public:
		Outbreak(const Infect&);
		// The infection that caused the outbreak.
		Infect infection;
	};
}

