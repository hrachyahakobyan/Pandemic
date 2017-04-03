#include "stdafx.h"
#include "Outbreak.h"

namespace pan{
	Outbreak::Outbreak(const Infect& inf):
	ActionImpl(ActionType::Outbreak),
	infection(inf)
	{
	}
}