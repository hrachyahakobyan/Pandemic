#pragma once
#include "Object.h"

namespace pan {
	/**
	*	@brief Describes different cards present in the game.
	*/
	enum class CardType : unsigned int{
		City = 0, Event, Epidemic, Infection
	};

	static const std::map<CardType, const char*> CardDescriptions{
		{CardType::City, "City Card"},
		{CardType::Event, "Event Card"},
		{CardType::Infection, "Infection Card"},
		{CardType::Epidemic, "Epidemic Card"}
	};
	/**
	*	@brief Abstract class to represent Card entity in the game.
	*	Cards contain an enum to differentiate their type.
	*	@author Hrachya Hakobyan
	*/
	class CardBase : public Object
	{
	public:
		virtual ~CardBase() = default;
		bool operator==(const CardBase&) const;
		inline bool operator!=(const CardBase&) const;
		const CardType type;
		virtual std::string description() const;
	public:
		CardBase(CardType type);
		virtual bool equals(const CardBase&) const{ return false; };
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object);
		}
	};

	bool CardBase::operator!=(const CardBase& o) const
	{
		return !((*this) == o);
	}

	template<CardType T>
	class CardImpl : public CardBase{};
}


