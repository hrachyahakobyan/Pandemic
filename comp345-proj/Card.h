#pragma once
#include "Object.h"

namespace pan {
	enum class CardType : unsigned int{
		Player = 0, Event, Infection
	};
	
	/**
	*	@brief Abstract class to represent Card entity in the game.
	*	Cards contain an enum to differentiate their type.
	*	@author Hrachya Hakobyan
	*/
	class CardBase : public Object
	{
	public:
		CardBase(CardType type);
		virtual ~CardBase() = default;
		const CardType type;
	};

	template<CardType T>
	class CardImpl : public CardBase{};
}

