#include "stdafx.h"
#include "EventCard.h"

namespace pan{
	CardImpl<CardType::Event>::CardImpl(EventType eventType) :
		CardBase(CardType::Event),
		eventType(eventType)
	{
	}
}
