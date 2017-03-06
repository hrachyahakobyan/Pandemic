#pragma once
#include "Card.h"

namespace pan{

	enum EventType : unsigned int{
		DummyEvent = 0
	};

	typedef CardImpl<CardType::Event> EventCard;

	/**
	*	@brief Represents the Event Card entity
	*	@author Hrachya Hakobyan
	*/
	template<>
	class CardImpl<CardType::Event> : public CardBase
	{
	public:
		CardImpl(EventType eventType);
		~CardImpl() = default;
		const EventType eventType;
		inline std::string description() const;
	};

	std::string CardImpl<CardType::Event>::description() const
	{
		return "Event card. Event: " + std::to_string(static_cast<std::underlying_type<EventType>::type>(eventType));
	}
}

