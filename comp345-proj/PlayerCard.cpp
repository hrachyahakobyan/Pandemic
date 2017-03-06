#include "stdafx.h"
#include "PlayerCard.h"


namespace pan{
	CardImpl<CardType::Player>::CardImpl(Map::CityIndex index) :
		CardBase(CardType::Player),
		index(index)
	{
	}
}
