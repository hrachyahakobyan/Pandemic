#include "stdafx.h"
#include "CityCard.h"

namespace pan{
	CardImpl<CardType::City>::CardImpl(CityIndex cIndex, RegionIndex rIndex) :
	CardBase(CardType::City),
	cityIndex(cIndex),
	regionIndex(rIndex)
	{
	}

	std::string CardImpl<CardType::City>::description() const
	{
		return CardBase::description() + ' ' + std::to_string(cityIndex) + ' ' + std::to_string(regionIndex);
	}
}