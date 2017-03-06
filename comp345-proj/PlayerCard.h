#pragma once
#include "Card.h"
#include "Map.h"

namespace pan{
	typedef CardImpl<CardType::Player> PlayerCard;

	/**
	*	@brief Represents the Player Card entitys
	*	@author Hrachya Hakobyan
	*/
	template<>
	class CardImpl<CardType::Player> : public CardBase
	{
	public:
		CardImpl(Map::CityIndex index);
		~CardImpl() = default;
		const Map::CityIndex index;
		inline std::string description() const;
	};

	std::string CardImpl<CardType::Player>::description() const
	{
		return "Player card. Index " + std::to_string(index);
	}
}
