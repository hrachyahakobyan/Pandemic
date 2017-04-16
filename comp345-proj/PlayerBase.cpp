#include "stdafx.h"
#include "PlayerBase.h"
#include "ReferenceCard.h"
#include "Player.h"
#include "CityCard.h"


namespace pan{
	PlayerBase::PlayerBase(PlayerIndex index) : index(index)
	{
	}

	PlayerBase::PlayerBase(PlayerIndex index, const std::string& name) :
	index(index),
    name(name)
	{
	}

	PlayerBase::~PlayerBase()
	{
	}

	bool PlayerBase::operator==(const PlayerBase& o) const
	{
		bool equals = (this->location == o.location && this->name == o.name && this->getRole() == o.getRole()
			&& this->cards.size() == o.cards.size() && this->index == o.index);
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

	bool PlayerBase::hasEventCard(EventType type) const
	{
		for (const auto& c : cards){
			if (c->type == CardType::Event){
				const auto card = std::static_pointer_cast<EventCard>(c);
				if (card->eventType == type){
					return true;
				}
			}
		}
		return false;
	}

	std::shared_ptr<EventCard> PlayerBase::removeEventCard(EventType type)
	{
		for (std::size_t i = 0; i < cards.size(); i++){
			if (cards[i]->type == CardType::Event){
				auto card = std::static_pointer_cast<EventCard>(cards[i]);
				if (card->eventType == type){
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
					if (iter == cards.end())
						break;
				}
				else {
					++iter;
				}
			}
			else {
				++iter;
			}
		}
		return removedCards;
	}

	std::string PlayerBase::description() const
	{
		std::string result = "Player: " + name + "\nIndex: " + std::to_string(index) + "\nRole: " + getRole().description() +
			"\nLocation: " + std::to_string(this->location) + "\nCards:\n";
		for (const auto& c : cards._Get_container()){
			result += c->description() + '\n';
		}
		return result;
	}
}