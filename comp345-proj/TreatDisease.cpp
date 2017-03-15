#include "stdafx.h"
#include "TreatDisease.h"

namespace pan{
	TreatDisease::TreatDisease(PlayerIndex player, DiseaseType dType) :
		player(player), diseaseType(dType)
	{
	}

	ActionBase* TreatDisease::clone() const
	{
		return new TreatDisease(*this);
	}
}
