#include "stdafx.h"
#include "EpidemicCard.h"

namespace pan{
	CardImpl<CardType::Epidemic>::CardImpl() :
	CardBase(CardType::Epidemic)
	{
	}

	CardBase* EpidemicCard::clone() const
	{
		return new EpidemicCard(*this);
	}
}