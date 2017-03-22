#include "stdafx.h"
#include "CityCard.h"

namespace pan{
	CardImpl<CardType::City>::CardImpl(CityIndex index) :
	CardBase(CardType::City),
	cityIndex(index)
	{
	}

	std::string CardImpl<CardType::City>::description() const
	{
		return CardBase::description() + ' ' + std::to_string(cityIndex);
	}
}