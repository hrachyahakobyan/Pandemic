#pragma once
#include "Card.h"

namespace pan{

	typedef CardImpl<CardType::City> CityCard;

	/**
	*	@brief Represents the City card entity.
	*	@author Hrachya Hakobyan
	*/
	template<>
	class CardImpl<CardType::City> : public CardBase
	{
	public:
		CardImpl(CityIndex index, RegionIndex region);
		~CardImpl() = default;
		const CityIndex cityIndex;
		const RegionIndex regionIndex;
		std::string description() const;
		inline bool operator==(const CardImpl&) const;
		inline bool operator!=(const CardImpl&) const;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CardBase);
			ar & boost::serialization::make_nvp("cityIndex", const_cast<CityIndex&>(cityIndex));
			ar & boost::serialization::make_nvp("regionIndex", const_cast<CityIndex&>(regionIndex));
		}
	};

	bool CardImpl<CardType::City>::operator==(const CardImpl& o) const
	{
		return cityIndex == o.cityIndex && regionIndex == o.regionIndex;
	}

	bool CardImpl<CardType::City>::operator!=(const CardImpl& o) const
	{
		return !(*this == o);
	}
}

namespace boost {
	namespace serialization {
		template<class Archive>
		inline void save_construct_data(
			Archive & ar, const pan::CardImpl<pan::CardType::City> * p, const unsigned int file_version
			){
			ar & boost::serialization::make_nvp("cityIndex", p->cityIndex);
			ar & boost::serialization::make_nvp("regionIndex", p->regionIndex);
		}

		template<class Archive>
		inline void load_construct_data(
			Archive & ar, pan::CardImpl<pan::CardType::City> * p, const unsigned int file_version
			){
			pan::CityIndex cityIndex;
			pan::RegionIndex regionIndex;
			ar & boost::serialization::make_nvp("cityIndex", cityIndex);
			ar & boost::serialization::make_nvp("regionIndex", regionIndex);
			::new(p)pan::CardImpl<pan::CardType::City>(cityIndex, regionIndex);
		}
	}
}

