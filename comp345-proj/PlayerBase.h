#pragma once
#include "Role.h"
#include "detail\Deck.h"
#include "ReferenceCard.h"
#include "CityCard.h"

namespace pan{
	/**
	*	@brief Base class for player objects.
	*	@author Hrachya Hakobyan
	*/
	class PlayerBase {
	public:
		virtual ~PlayerBase();

		bool operator==(const PlayerBase&) const;
		inline bool operator!=(const PlayerBase&) const;

		inline const std::string& getName() const;
		inline void setName(const std::string& name);

		inline CityIndex getLocation() const;
		inline void setLocation(CityIndex);

		inline detail::Deck<std::shared_ptr<CardBase>>& getCards();
		inline const detail::Deck<std::shared_ptr<CardBase>>& getCards() const;
		inline void setCards(const detail::Deck<std::shared_ptr<CardBase>>&);

		std::string description() const;

		const RoleBase role;
		const ReferenceCard referenceCard;

		bool hasCityCard(CityIndex) const;
		std::shared_ptr<CityCard> removeCityCard(CityIndex index);
		std::size_t countCardsMatching(const CardBase& card) const;
		std::size_t countCardsMatchingRegion(RegionIndex index) const;
		detail::Deck<std::shared_ptr<CityCard>> removeCardsMatchingRegion(RegionIndex region, std::size_t count);

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_NVP(name);
			ar & BOOST_SERIALIZATION_NVP(location);
			ar & BOOST_SERIALIZATION_NVP(cards);
		}
	protected:
		PlayerBase(const RoleBase& role);
		PlayerBase(const RoleBase& role, const std::string& name);

		detail::Deck<std::shared_ptr<CardBase>> cards;
		std::string name;
		CityIndex location;
#ifdef _DEBUG
#ifndef DISABLE_TESTS
		friend class PlayerTest;
		FRIEND_TEST(PlayerTest, compares);
		FRIEND_TEST(PlayerTest, serializes);
		FRIEND_TEST(PlayerTest, serializesContainer);
#endif
#endif
	};

	bool PlayerBase::operator!=(const PlayerBase& o) const
	{
		return !((*this) == o);
	}

	const std::string& PlayerBase::getName() const
	{
		return name;
	}

	void PlayerBase::setName(const std::string& name)
	{
		this->name = name;
	}

	CityIndex PlayerBase::getLocation() const
	{
		return location;
	}

	void PlayerBase::setLocation(CityIndex loc)
	{
		this->location = loc;
	}

	detail::Deck<std::shared_ptr<CardBase>>& PlayerBase::getCards()
	{
		return cards;
	}

	const detail::Deck<std::shared_ptr<CardBase>>& PlayerBase::getCards() const
	{
		return cards;
	}

	void PlayerBase::setCards(const detail::Deck<std::shared_ptr<CardBase>>& cards)
	{
		this->cards = cards;
	}
}

/**
*	Since the class does not have default constructors, we need this
*	to avoid compilation errors when attempting to (de)serialize 
*	types of PlayerBase*. This methods do not do anything, since
*	we are not going to have actual PlayerBase instances in the program.
*/
namespace boost {
	namespace serialization {
		template<class Archive>
		inline void save_construct_data(
			Archive & ar, const pan::PlayerBase * p, const unsigned int file_version
			){
		}

		template<class Archive>
		inline void load_construct_data(
			Archive & ar, pan::PlayerBase * p, const unsigned int file_version
			){
		}
	}
} 

