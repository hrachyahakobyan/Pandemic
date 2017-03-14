#include "stdafx.h"
#include "Outbreak.h"

namespace pan{
	Outbreak::Outbreak(const Infect& inf):
		infection(inf)
	{
	}

	ActionBase* Outbreak::clone() const
	{
		return new Outbreak(*this);
	}
}