#include "stdafx.h"
#include "CityCard.h"

namespace pan{
	CardImpl<CardType::City>::CardImpl(Map::CityIndex index) :
	CardBase(CardType::City),
	cityIndex(index)
	{
	}
}