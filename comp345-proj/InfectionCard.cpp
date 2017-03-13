#include "stdafx.h"
#include "InfectionCard.h"

namespace pan{
	CardImpl<CardType::Infection>::CardImpl(Map::CityIndex index) :
		CardBase(CardType::Infection),
		cityIndex(index)
	{
	}
}
