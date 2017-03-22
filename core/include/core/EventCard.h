#pragma once
#include "Card.h"

namespace pan{

	/**
	*	@brief describes the different event cards present in the game.
	*/
	enum EventType : unsigned int{
		Airlift = 0, GovGrant, ResilientPopulation, OneQuietNight, Forecast
	};

	static const std::map<EventType, const char*> EventTypeDescriptions{
		{EventType::Airlift, "Airlift"},
		{EventType::GovGrant, "Government Grant" },
		{EventType::ResilientPopulation, "Resilient Population"},
		{ EventType::OneQuietNight, "One quiet night" },
		{EventType::Forecast, "Forecast"}
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
		std::string description() const;
		inline bool operator==(const CardImpl&) const;
		inline bool operator!=(const CardImpl&) const;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CardBase);
			ar & boost::serialization::make_nvp("eventType", const_cast<EventType&>(eventType));
		}
	};

	bool CardImpl<CardType::Event>::operator==(const CardImpl& o) const
	{
		return eventType == o.eventType;
	}

	bool CardImpl<CardType::Event>::operator!=(const CardImpl& o) const
	{
		return eventType != o.eventType;
	}
}

namespace boost {
	namespace serialization {
		template<class Archive>
		inline void save_construct_data(
			Archive & ar, const pan::CardImpl<pan::CardType::Event> * p, const unsigned int file_version
			){
			ar & boost::serialization::make_nvp("eventType", p->eventType);
		}

		template<class Archive>
		inline void load_construct_data(
			Archive & ar, pan::CardImpl<pan::CardType::Event> * p, const unsigned int file_version
			){
			pan::EventType type;
			ar & boost::serialization::make_nvp("eventType", type);
			::new(p)pan::CardImpl<pan::CardType::Event>(type);
		}
	}
}





