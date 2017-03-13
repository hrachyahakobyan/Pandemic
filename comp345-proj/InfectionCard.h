#pragma once
#include "Card.h"
#include "Map.h"

 namespace pan{

	typedef CardImpl<CardType::Infection> InfectionCard;
	/**
	*	@brief Represents the Infection card entity.
	*	@author Hrachya Hakobyan
	*/
	template<>
	class CardImpl<CardType::Infection> : public CardBase
	{
	public:
		CardImpl(Map::CityIndex index);
		~CardImpl() = default;
		const Map::CityIndex cityIndex;
		inline std::string description() const;
		inline bool operator==(const CardImpl&) const;
		inline bool operator!=(const CardImpl&) const;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CardBase);
			ar & boost::serialization::make_nvp("cityIndex", const_cast<Map::CityIndex&>(cityIndex));
		}
	};

	bool CardImpl<CardType::Infection>::operator==(const CardImpl& o) const
	{
		return cityIndex == o.cityIndex;
	}

	bool CardImpl<CardType::Infection>::operator!=(const CardImpl& o) const
	{
		return cityIndex != o.cityIndex;
	}

	std::string CardImpl<CardType::Infection>::description() const
	{
		return CardBase::description() + ' ' + std::to_string(cityIndex);
	}
}

namespace boost {
	namespace serialization {
		template<class Archive>
		inline void save_construct_data(
			Archive & ar, const pan::CardImpl<pan::CardType::Infection> * p, const unsigned int file_version
			){
			ar & boost::serialization::make_nvp("cityIndex", p->cityIndex);
		}

		template<class Archive>
		inline void load_construct_data(
			Archive & ar, pan::CardImpl<pan::CardType::Infection> * p, const unsigned int file_version
			){
			pan::Map::CityIndex index;
			ar & boost::serialization::make_nvp("cityIndex", index);
			::new(p)pan::CardImpl<pan::CardType::Infection>(index);
		}
	}
}