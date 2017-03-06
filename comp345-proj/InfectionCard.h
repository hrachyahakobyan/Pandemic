#pragma once
#include "Card.h"

namespace pan{
	typedef CardImpl<CardType::Infection> InfectionCard;

	/**
	*	@brief Represents the Infection Card entity
	*	@author Hrachya Hakobyan
	*/
	template<>
	class CardImpl<CardType::Infection> : public CardBase
	{
	public:
		CardImpl();
		~CardImpl() = default;
		inline std::string description() const;
	};

	std::string CardImpl<CardType::Infection>::description() const
	{
		return "Infection card";
	}
}

