#pragma once
#include "Object.h"

namespace pan {
	/**
	*	@brief Abstract class to represent Card entity in the game
	*	@author Hrachya Hakobyan
	*/
	class Card : public Object
	{
	public:
		Card();
		virtual ~Card();
	};
}

