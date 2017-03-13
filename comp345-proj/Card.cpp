#include "stdafx.h"
#include "Card.h"

namespace pan{
	CardBase::CardBase(CardType type) :
		type(type)
	{
	}

	std::string CardBase::description() const
	{
		return CardDescriptions.at(type);
	}
}
