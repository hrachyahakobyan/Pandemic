#include "stdafx.h"
#include "PlayerBase.h"
#include "ReferenceCard.h"
#include "Player.h"
#include "CityCard.h"


namespace pan{
	PlayerBase::PlayerBase(const RoleBase& role) :
	role(role)
	{
	}

	PlayerBase::PlayerBase(const RoleBase& role,const std::string& name) :
	role(role),
    name(name)
	{
	}

	PlayerBase::~PlayerBase()
	{
	}

	bool PlayerBase::operator==(const PlayerBase& o) const
	{
		bool equals = (this->location == o.location && this->name == o.name && this->role == o.role
			&& this->cards.size() == o.cards.size());
		if (!equals)
			return false;
		for (std::size_t i = 0; i < cards.size(); i++){
			if (*cards[i] != *o.cards[i])
				return false;
		}
		return true;
	}

	bool PlayerBase::hasCityCard(CityIndex index) const
	{
		for (const auto& c : cards){
			if(c->type == CardType::City){
				const auto card = std::static_pointer_cast<CityCard>(c);
				if (card->cityIndex == index){
					return true;
				}
			}
		}
		return false;
	}

	std::shared_ptr<CityCard> PlayerBase::removeCityCard(CityIndex index)
	{
		for (std::size_t i = 0; i < cards.size(); i++){
			if (cards[i]->type == CardType::City){
				auto card = std::static_pointer_cast<CityCard>(cards[i]);
				if (card->cityIndex == index){
					cards.erase(cards.begin() + i);
					return card;
				}
			}
		}
		return nullptr;
	}

	std::size_t PlayerBase::countCardsMatching(const CardBase& card) const
	{
		std::size_t result = 0;
		for (const auto& c : cards){
			if (c->operator==(card))
				result++;
		}
		return result;
	}

	std::size_t PlayerBase::countCardsMatchingRegion(RegionIndex r) const
	{
		std::size_t result = 0;
		for (const auto& c : cards){
			if (c->type == CardType::City){
				if (std::static_pointer_cast<CityCard>(c)->regionIndex == r)
					result++;
			}
		}
		return result;
	}

	detail::Deck<std::shared_ptr<CityCard>> PlayerBase::removeCardsMatchingRegion(RegionIndex region, std::size_t count){
		detail::Deck<std::shared_ptr<CityCard>> removedCards;
		for (auto iter = cards.begin(); iter != cards.end();) {
			if (removedCards.size() == count)
				return removedCards;
			if ((*iter)->type == CardType::City){
				std::shared_ptr<CityCard> cityCard = std::static_pointer_cast<CityCard>(*iter);
				if (cityCard->regionIndex == region){
					removedCards.push(cityCard);
					iter = cards.erase(iter);
				}
			}
		}
		return removedCards;
	}

	std::string PlayerBase::description() const
	{
		std::string result = "Player: " + name + "\nRole: " + role.description() +
			"\nLocation: " + std::to_string(this->location) + "\nCards:\n";
		for (const auto& c : cards._Get_container()){
			result += c->description() + '\n';
		}
		return result;
	}
}