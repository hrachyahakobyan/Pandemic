#include "stdafx.h"
#include "ActionHandler.h"
#include "Move.h"
#include "Game.h"
#include "Infect.h"
#include "Outbreak.h"
#include "Epidemic.h"
#include "DirectFlight.h"
#include "CityCard.h"
#include "CharterFlight.h"
#include "ShuttleFlight.h"
#include "BuildResearchStation.h"

namespace pan{

	ActionHandler::ActionHandler(Game& game) :
		game(game)
	{
	}

	ActionHandler::~ActionHandler()
	{
	}

	template<>
	bool ActionHandler::validate<Move>(const Move& m) const{
		// Check if parameters are valid
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the target city is within single step reach
		Map::ConnectedCityIterator ai, ai_end;
		bool isReachable = false;
		for (boost::tie(ai, ai_end) = game.map.connectedCities(player.getLocation());
			ai != ai_end; ++ai){
			if (*ai == m.targetCity){
				isReachable = true;
				break;
			}
		}
		return isReachable;
	}

	template<>
	bool ActionHandler::execute<Move>(const Move& m) const{
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.player);
		// Remove from previous city
		game.map[player.getLocation()].removePlayer(m.player);
		// Add to the target city
		game.map[m.targetCity].addPlayer(m.player);
		// Update the player's location
		player.setLocation(m.targetCity);
		return true;
	}

	template<>
	bool ActionHandler::validate<DirectFlight>(const DirectFlight& m) const{
		// Check if parameters are valid
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the player has a matching card
		bool hasMatchingCard = false;
		for (const auto& card : player.getCards()._Get_container()){
			if (card->type == CardType::City)
			{
				if (static_cast<const CityCard*>(card.get())->cityIndex == m.targetCity){
					hasMatchingCard = true;
					break;
				}
			}
		}
		return hasMatchingCard;
	}

	template<>
	bool ActionHandler::execute<DirectFlight>(const DirectFlight& m) const{
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.player);
		// Remove the city card and put into discard pile
		auto& cards = player.getCards();
		for (std::size_t i = 0; i < cards.size(); i++){
			if (cards[i]->type == CardType::City)
			{
				if (static_cast<const CityCard*>(cards[i].get())->cityIndex == m.targetCity){
					game.deckData.playerDiscardDeck.push(cards[i]);
					cards.erase(cards.begin() + i);
					break;
				}
			}
		}
		// Remove from previous city
		game.map[player.getLocation()].removePlayer(m.player);
		// Add to the target city
		game.map[m.targetCity].addPlayer(m.player);
		// Update the player's location
		player.setLocation(m.targetCity);
		return true;
	}

	template<>
	bool ActionHandler::validate<CharterFlight>(const CharterFlight& m) const{
		// Check if parameters are valid
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the player has a matching card to the city he is in
		bool hasMatchingCard = false;
		for (const auto& card : player.getCards()._Get_container()){
			if (card->type == CardType::City)
			{
				if (static_cast<const CityCard*>(card.get())->cityIndex == 
					player.getLocation()){
					hasMatchingCard = true;
					break;
				}
			}
		}
		return hasMatchingCard;
	}

	template<>
	bool ActionHandler::execute<CharterFlight>(const CharterFlight& m) const{
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.player);
		// Remove the city card and put it in the discard pile
		auto& cards = player.getCards();
		for (std::size_t i = 0; i < cards.size(); i++){
			if (cards[i]->type == CardType::City)
			{
				if (static_cast<const CityCard*>(cards[i].get())->cityIndex ==
					player.getLocation()){
					// Put to the discard pile 
					game.deckData.playerDiscardDeck.push(cards[i]);
					// Erase from player
					cards.erase(cards.begin() + i);
					break;
				}
			}
		}
		// Remove from previous city
		game.map[player.getLocation()].removePlayer(m.player);
		// Add to the target city
		game.map[m.targetCity].addPlayer(m.player);
		// Update the player's location
		player.setLocation(m.targetCity);
		return true;
	}

	template<>
	bool ActionHandler::validate<ShuttleFlight>(const ShuttleFlight& m) const{
		// Check if parameters are valid
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the player both the player's location
		// and the target location have research stations
		return (game.map[player.getLocation()].researchStation &&
				game.map[m.targetCity].researchStation);
	}

	template<>
	bool ActionHandler::execute<ShuttleFlight>(const ShuttleFlight& m) const{
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.player);
		// Remove from previous city
		game.map[player.getLocation()].removePlayer(m.player);
		// Add to the target city
		game.map[m.targetCity].addPlayer(m.player);
		// Update the player's location
		player.setLocation(m.targetCity);
		return true;
	}

	template<>
	bool ActionHandler::validate<BuildResearchStation>(const BuildResearchStation& m) const{
		// Check if parameters are valid
		if (!game.playerExists(m.player)){
			return false;
		}
		// Check if maximum research stations is reached
		if (game.gameData.researchStations == game.gameData.settings.maxResearchStations)
			return false;
		// Check if the city already has a research station
		const auto& player = game.getPlayer(m.player);
		if (game.map[player.getLocation()].researchStation)
			return false;
		// Check if the player has a matching card to the city he is in
		bool hasMatchingCard = false;
		for (const auto& card : player.getCards()._Get_container()){
			if (card->type == CardType::City)
			{
				if (static_cast<const CityCard*>(card.get())->cityIndex ==
					player.getLocation()){
					hasMatchingCard = true;
					break;
				}
			}
		}
		return hasMatchingCard;
	}

	template<>
	bool ActionHandler::execute<BuildResearchStation>(const BuildResearchStation& m) const{
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.player);
		// Remove the city card and put it in the discard pile
		auto& cards = player.getCards();
		for (std::size_t i = 0; i < cards.size(); i++){
			if (cards[i]->type == CardType::City)
			{
				if (static_cast<const CityCard*>(cards[i].get())->cityIndex ==
					player.getLocation()){
					// Put to the discard pile 
					game.deckData.playerDiscardDeck.push(cards[i]);
					// Erase from player
					cards.erase(cards.begin() + i);
					break;
				}
			}
		}
		// add research station to the city
		game.map[player.getLocation()].researchStation = true;
		// Increment research stations
		game.gameData.researchStations++;
		return true;
	}

	template<>
	bool ActionHandler::validate<Outbreak>(const Outbreak& a) const{
		const auto& city = game.map[a.infection.city];
		// If the city does not have 3 cubes of the specified type,
		// the outbreak will not take place
		if (city.getCubes(a.infection.diseaseType) != 3){
			return false;
		} 
		return true;
	}

	template<>
	bool ActionHandler::execute<Outbreak>(const Outbreak& a) const{
		if (!a.validate(*this)){
			return false;
		}
		// The current city has already suffered an outbreak due to the same infection
		if (a.infection.outbreakedCities.find(a.infection.city) != a.infection.outbreakedCities.end()){
			return true;
		}
		// Check the outbreak marker
		// If it is on max, the game is lost
		if (game.gameData.outbreakMarker == game.gameData.settings.outbreakMarkerMax){
			game.changeStatus(Game::Status::Defeat);
			return true;
		}
		// Increase outbreak marker
		game.gameData.outbreakMarker++;
		// Otherwise, infect each neighbor
		Map::ConnectedCityIterator ai, ai_end;
		bool result = true;
		for (boost::tie(ai, ai_end) = game.map.connectedCities(a.infection.city);
			ai != ai_end; ++ai){
			// Create a new infection whose target is the neighbor
			Infect infect(*ai, a.infection.diseaseType, 1);
			infect.outbreakedCities = a.infection.outbreakedCities;
			// Add the currently outbreaked city to the set of outbreaked cities
			// of the new infection
			infect.outbreakedCities.insert(a.infection.city);
			result = result && infect.execute(*this);
		}
		return result;
	}

	template<>
	bool ActionHandler::validate<Infect>(const Infect& a) const{
		// Check the valid number of cubes
		if (!(a.cubes > 0 && a.cubes < 4))
			return false;
		// A city cannot receive more than 1 cube of a disease that is different from the city's
		// region
		// Different diseases
		if (game.map.regionForCity(a.city) != a.diseaseType){
			if (a.cubes != 1)
				return false;
		}
		return true;
	}

	template<>
	bool ActionHandler::execute<Infect>(const Infect& a) const{
		if (!a.validate(*this)){
			return false;
		}
		// Get the city reference
		auto& city = game.map[a.city];
		// The current cubes of the city of the givem diseaseType
		std::size_t currentCubes = city.getCubes(a.diseaseType);
		// How many more the city is able to take
		std::size_t canTake = 3 - currentCubes;
		// How many cubes are left in the game
		std::size_t cubesLeft = game.gameData.diseaseCubes[a.diseaseType];
		// How many the city will actually take
		// The minimum of how many it can actually take, and how many it is required to take
		std::size_t willTake = std::min(canTake, a.cubes);
		// If there are less cubes left than the city will actually take
		// automatically the game is lost.
		if (willTake > cubesLeft){
			game.changeStatus(Game::Status::Defeat);
			return true;
		}
		// Otherwise, increase the number of cubes in the city
		city.setCubes(a.diseaseType, currentCubes + willTake);
		// And decrease from cubes left
		game.gameData.diseaseCubes[a.diseaseType] = cubesLeft - willTake;

		// Outbreak if there city took less cubes than it should have
		if (willTake < a.cubes){
			Outbreak out(a);
			return out.execute(*this);
		}
		return true;
	}

	template<>
	bool ActionHandler::validate<Epidemic>(const Epidemic& a) const{
		return true;
	}

	template<>
	bool ActionHandler::execute<Epidemic>(const Epidemic& a) const{
		if (!a.validate(*this)){
			return false;
		}
		// Increase the infection rate if possible
		if (game.gameData.infectionRateMarker + 1 < game.gameData.settings.infectionRates.size()){
			game.gameData.infectionRateMarker++;
		}
		// Infect if possible
		if (!game.deckData.infectionDeck.empty()){
			// Get the card and infect
			auto infectionCard = game.deckData.infectionDeck.bottom();
			game.deckData.infectionDeck.pop_bottom();
			Infect infect(infectionCard->cityIndex, game.map.regionForCity(infectionCard->cityIndex), 3);
			infect.execute(*this);
			// Put the card on the discard pile
			game.deckData.infectionDiscardDeck.push(infectionCard);
			// Check the game condition. Might have lost prematurely
			if (game.isOver())
				return true;
		}
		// Intensify
		auto discardedCards = std::move(game.deckData.infectionDiscardDeck);
		srand(static_cast<unsigned int>(time(NULL)));
		discardedCards.shuffle();
		game.deckData.infectionDeck.push(discardedCards);
		return true;
	}
}