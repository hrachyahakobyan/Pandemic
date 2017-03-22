#include "stdafx.h"
#include "InfectionCard.h"

namespace pan{
	CardImpl<CardType::Infection>::CardImpl(CityIndex index) :
		CardBase(CardType::Infection),
		cityIndex(index)
	{
	}

	std::string CardImpl<CardType::Infection>::description() const
	{
		return CardBase::description() + ' ' + std::to_string(cityIndex);
	}
}
