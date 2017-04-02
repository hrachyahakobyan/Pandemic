#pragma once
#include "Card.h"

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
		CardImpl(CityIndex index);
		~CardImpl() = default;
		const CityIndex cityIndex;
		std::string description() const;
		inline bool operator==(const CardImpl&) const;
		inline bool operator!=(const CardImpl&) const;
		CardBase* clone() const;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar.template register_type<pan::CardBase>();
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CardBase);
			ar & boost::serialization::make_nvp("cityIndex", const_cast<CityIndex&>(cityIndex));
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
			pan::CityIndex index;
			ar & boost::serialization::make_nvp("cityIndex", index);
			::new(p)pan::CardImpl<pan::CardType::Infection>(index);
		}
	}
}