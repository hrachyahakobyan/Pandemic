#include "stdafx.h"
#include "EventCard.h"

namespace pan{
	CardImpl<CardType::Event>::CardImpl(EventType eventType) :
		CardBase(CardType::Event),
		eventType(eventType)
	{
	}

	std::string CardImpl<CardType::Event>::description() const
	{
		return CardBase::description() + ' ' + EventTypeDescriptions.at(eventType);
	}

	CardBase* EventCard::clone() const
	{
		return new EventCard(*this);
	}
}
