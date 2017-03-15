#include "stdafx.h"
#include "CityCard.h"

namespace pan{
	CardImpl<CardType::City>::CardImpl(CityIndex index) :
	CardBase(CardType::City),
	cityIndex(index)
	{
	}
}