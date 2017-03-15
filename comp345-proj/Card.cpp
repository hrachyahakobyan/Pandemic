#include "stdafx.h"
#include "Card.h"
#include "Cards.h"

namespace pan{
	CardBase::CardBase(CardType type) :
		type(type)
	{
	}

	std::string CardBase::description() const
	{
		return CardDescriptions.at(type);
	}

	bool CardBase::operator==(const CardBase& o) const
	{
		if (type != o.type)
			return false;
		if (type == CardType::City){
			return static_cast<const CityCard&>(*this) ==
				static_cast<const CityCard&>(o);
		}
		else if (type == CardType::Event){
			return static_cast<const EventCard&>(*this) ==
				static_cast<const EventCard&>(o);
		}
		else if (type == CardType::Infection){
			return static_cast<const InfectionCard&>(*this) ==
				static_cast<const InfectionCard&>(o);
		}
		return true;
	}
}
