#pragma once
#include "Card.h"

namespace pan{
	typedef CardImpl<CardType::Epidemic> EpidemicCard;
	/**
	*	@brief Represents the Epidemic card entity
	*	@author Hrachya Hakobyan
	*/
	template<>
	class CardImpl<CardType::Epidemic> : public CardBase
	{
	public:
		CardImpl();
		~CardImpl() = default;
		inline bool operator==(const CardImpl&)const;
		inline bool operator!=(const CardImpl&)const;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CardBase);
		}
	};

	bool CardImpl<CardType::Epidemic>::operator==(const CardImpl& o) const
	{
		return true;
	}

	bool CardImpl<CardType::Epidemic>::operator!=(const CardImpl& o) const
	{
		return false;
	}
}