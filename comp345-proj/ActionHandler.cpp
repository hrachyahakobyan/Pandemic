#include "stdafx.h"
#include "ActionHandler.h"
#include "Game.h"
#include "Actions.h"
#include "Cards.h"


namespace pan{

	ActionHandler::ActionHandler(Game& game) :
		game(game)
	{
	}

	ActionHandler::~ActionHandler()
	{
	}


	/**
	*	Validates Move action. A move action is valid if the following hold
	*	1.The player exists.
	*	2. It is the player's turn.
	*	3. The player can make an action.
	*	4. The target city is not the same as the player's city.
	*	5. The target city is a neighbor of the player's city.
	*/
	template<>
	bool ActionHandler::validate<Move>(const Move& m) const{
		// Check if parameters are valid
		if (!game.stateMachine.getMap().cityExists(m.targetCity) ||
			!game.stateMachine.playerExists(m.player) ||
			!game.stateMachine.playerCanAct(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the destination is a neighbor of the players location
		return game.stateMachine.getMap().connectionExists(m.targetCity, player.getLocation());
	}

	template<>
	bool ActionHandler::execute<Move>(const Move& m){
		if (!m.validate(*this)){
			return false;
		}
		game.stateMachine.movePlayer(m.player, m.targetCity);
		game.stateMachine.playerDidAct(m.player, m.getActionType());
		return true;
	}

	template<>
	bool ActionHandler::validate<DirectFlight>(const DirectFlight& m) const{
		// Check if parameters are valid
		if (!game.stateMachine.getMap().cityExists(m.targetCity) ||
			!game.stateMachine.playerExists(m.player) || 
			!game.stateMachine.playerCanAct(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the player has a matching card
		return player.hasCityCard(m.targetCity);
	}

	template<>
	bool ActionHandler::execute<DirectFlight>(const DirectFlight& m){
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.stateMachine.getPlayer(m.player);
		// Remove the city card and put into discard pile
		CardBasePtr cardToRemove = player.removeCityCard(m.targetCity);
		game.stateMachine.discardPlayerCard(cardToRemove);
		game.stateMachine.movePlayer(m.player, m.targetCity);
		game.stateMachine.playerDidAct(m.player, m.getActionType());
		return true;
	}

	template<>
	bool ActionHandler::validate<CharterFlight>(const CharterFlight& m) const{
		// Check if parameters are valid
		if (!game.stateMachine.getMap().cityExists(m.targetCity) ||
			!game.stateMachine.playerExists(m.player) ||
			!game.stateMachine.playerCanAct(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		return player.hasCityCard(player.getLocation());
	}

	template<>
	bool ActionHandler::execute<CharterFlight>(const CharterFlight& m){
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.stateMachine.getPlayer(m.player);
		// Remove the city card and put it in the discard pile
		CardBasePtr cardToRemove = player.removeCityCard(player.getLocation());
		game.stateMachine.discardPlayerCard(cardToRemove);
		// Move the player
		game.stateMachine.movePlayer(m.player, m.targetCity);
		game.stateMachine.playerDidAct(m.player, m.getActionType());
		return true;
	}

	template<>
	bool ActionHandler::validate<ShuttleFlight>(const ShuttleFlight& m) const{
		// Check if parameters are valid
		if (!game.stateMachine.getMap().cityExists(m.targetCity) ||
			!game.stateMachine.playerExists(m.player) ||
			!game.stateMachine.playerCanAct(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the player both the player's location
		// and the target location have research stations
		return (game.stateMachine.getMap()[player.getLocation()].researchStation &&
				game.stateMachine.getMap()[m.targetCity].researchStation);
	}

	template<>
	bool ActionHandler::execute<ShuttleFlight>(const ShuttleFlight& m){
		if (!m.validate(*this)){
			return false;
		}
		game.stateMachine.movePlayer(m.player, m.targetCity);
		game.stateMachine.playerDidAct(m.player, m.getActionType());
		return true;
	}

	template<>
	bool ActionHandler::validate<BuildResearchStation>(const BuildResearchStation& m) const{
		// Check if parameters are valid
		if (!game.stateMachine.playerExists(m.player)
			|| !game.stateMachine.playerCanAct(m.player)){
			return false;
		}
		// Check if maximum research stations is reached
		if (game.stateMachine.researchStationsMaxedOut())
			return false;
		// Check if the city already has a research station
		const auto& player = game.getPlayer(m.player);
		if (game.stateMachine.getMap()[player.getLocation()].researchStation)
			return false;
		// Check if the player has a matching card to the city he is in
		return player.hasCityCard(player.getLocation());
	}

	template<>
	bool ActionHandler::execute<BuildResearchStation>(const BuildResearchStation& m){
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.stateMachine.getPlayer(m.player);
		CardBasePtr cardToRemove = player.removeCityCard(player.getLocation());
		game.stateMachine.discardPlayerCard(cardToRemove);
		game.stateMachine.addResearchStation(player.getLocation());
		game.stateMachine.playerDidAct(m.player, m.getActionType());
		return true;
	}

#pragma message("Validate disease type parameter")
	template<>
	bool ActionHandler::validate<TreatDisease>(const TreatDisease& m) const{
		// Check if parameters are valid
		if (!game.stateMachine.playerExists(m.player) ||
			!game.stateMachine.playerCanAct(m.player)){
			return false;
		}
		const PlayerBase& player = game.getPlayer(m.player);
		// Check if the city the player is in has a disease cube
		// of the specified type
		std::size_t cityCubes = game.stateMachine.getMap()[player.getLocation()].getCubes(m.diseaseType);
		if (cityCubes == 0)
			return false;
		return true;
	}

	template<>
	bool ActionHandler::execute<TreatDisease>(const TreatDisease& m){
		if (!m.validate(*this)){
			return false;
		}
		const PlayerBase& player = game.getPlayer(m.player);
		auto& city = game.stateMachine.getMap()[player.getLocation()];
		std::size_t cityCubes = city.getCubes(m.diseaseType);
		// whether the disease is cured
		bool isCured = game.stateMachine.getGameData().diseases[m.diseaseType].getIsCured();
		// If the disease is cured, remove all cubes of the specified type
		std::size_t toRemove = (isCured ? cityCubes : 1);
		// Remove cubes from the city
		game.stateMachine.removeDiseaseCubesOfType(m.diseaseType, toRemove, player.getLocation());
		game.stateMachine.playerDidAct(m.player, m.getActionType());
		return true;
	}

	/**
	*	@brief validates the discover cure action
	*	The action is valid if the following hold
	*	1. The initiating player exists.
	*	2. The initiating player may perform an action.
	*	3. The initiating player is located in a city that has a research station
	*	4. The initiating player has enough city cards of the same color as the disease
	*	he/she attempts to cure.
	*/
	template<>
	bool ActionHandler::validate<DiscoverCure>(const DiscoverCure& m) const{
		// Check if parameters are valid
		if (!game.stateMachine.playerExists(m.player) ||
			!game.stateMachine.playerCanAct(m.player)){
			return false;
		}
		// Check if the disease is already cured
		if (game.stateMachine.getGameData().diseases[m.diseaseType].getIsCured())
			return false;
		// Check if has a research station
		const PlayerBase& p = game.getPlayer(m.player);
		if (!game.stateMachine.getMap()[p.getLocation()].researchStation)
			return false;
		return p.countCardsMatchingRegion(m.diseaseType) >= game.stateMachine.getGameData().settings.discoverCureCardCount;
	}

	template<>
	bool ActionHandler::execute<DiscoverCure>(const DiscoverCure& m){
		if (!m.validate(*this)){
			return false;
		}
		PlayerBase& p = game.stateMachine.getPlayer(m.player);
		auto removedCards = p.removeCardsMatchingRegion(m.diseaseType, game.stateMachine.getGameData().settings.discoverCureCardCount);
		game.stateMachine.discardPlayerCards(removedCards);
		// cure the disease
		game.stateMachine.cureDisease(m.diseaseType);
		game.stateMachine.playerDidAct(m.player, m.getActionType());
		return true;
	}

	/**
	*	@brief validates DrawplayerCards action
	*	the action is valid if the following hold
	*	1. The initiating player exists
	*	2. It's the initiating player's turn
	*	3. The current player stage is Draw
	*/
	template<>
	bool ActionHandler::validate<DrawPlayerCards>(const DrawPlayerCards& a) const{
		return (game.stateMachine.playerExists(a.player) && 
			    game.stateMachine.isPlayersTurn(a.player) &&
				game.stateMachine.getPlayerData().stage == PlayerStage::Draw);
	}

	template<>
	bool ActionHandler::execute<DrawPlayerCards>(const DrawPlayerCards& a){
		if (!a.validate(*this)){
			return false;
		}
		auto cards = game.stateMachine.drawPlayerDeckTop(game.stateMachine.getGameData().settings.playerDrawCount);
		// Check for game over in case not enough cards were drawn
		if (game.stateMachine.getGameData().state == GameState::Defeat)
			return true;
		PlayerBase& player = game.stateMachine.getPlayer(a.player);
		for (const auto& card : cards){
			if (card->type == CardType::Epidemic){
				Epidemic e;
				e.execute(*this);
				// If after the execution the game is over, no point to continue
				if (game.isOver())
					return true;
			}
			// Add the card to the player deck
			else {
				player.getCards().push(card);
			}
		}
		game.stateMachine.playerDidAct(a.player, a.getActionType());
		return true;
	}

	/**
	*	@brief validates PlayerInfect action
	*	The action is valid if the following hold.
	*	1. The initiating player exists.
	*	2. It is the initiating player's turn.
	*	3. The current stage is Infect.
	*/
	template<>
	bool ActionHandler::validate<PlayerInfect>(const PlayerInfect& a) const{
		return (game.stateMachine.playerExists(a.player) &&
			game.stateMachine.isPlayersTurn(a.player) &&
			game.stateMachine.getPlayerData().stage == PlayerStage::Infect);
	}

	template<>
	bool ActionHandler::execute<PlayerInfect>(const PlayerInfect& a){
		if (!a.validate(*this)){
			return false;
		}
		auto cards = game.stateMachine.drawInfectionDeckTop(game.stateMachine.getInfectCount());
		for (const auto& card : cards){
			Infect inf(card->cityIndex, game.stateMachine.getMap()[card->cityIndex].getRegion(), 1);
			inf.execute(*this);
			// Check for game over condition
			// No point to continue
			if (game.isOver())
				return true;
		}
		game.stateMachine.playerDidAct(a.player, a.getActionType());
		return true;
	}

	/**
	*	validates DiscardCard action
	*	The action is valid if the following hold.
	*	1. The initiating player exists.
	*	2. It is the initiating player's turn.
	*	3. The current stage is Discard.
	*	4. The index is a valid card in the players hand.
	*/
	template<>
	bool ActionHandler::validate<DiscardCard>(const DiscardCard& a) const{
		if (!(game.stateMachine.playerExists(a.player) &&
			game.stateMachine.isPlayersTurn(a.player) &&
			game.stateMachine.getPlayerData().stage == PlayerStage::Discard))
			return false;
		const PlayerBase& p = game.getPlayer(a.player);
		return p.getCards().size() > a.index;
	}

	template<>
	bool ActionHandler::execute<DiscardCard>(const DiscardCard& a){
		if (!a.validate(*this)){
			return false;
		}
		// Remove the card to the discard pile
		PlayerBase& player = game.stateMachine.getPlayer(a.player);
		detail::Deck<CardBasePtr>& cards = player.getCards();
		game.stateMachine.discardPlayerCard(cards[a.index]);
		cards.erase(cards.begin() + a.index);
		// Check if the player has the required number of cards
		game.stateMachine.playerDidAct(a.player, a.getActionType());
		return true;
	}

	/**
	*	Validates Share knowledge action
	*	The action is valid if the following hold.
	*	1. The initiating player exists.
	*	2. The target player exists
	*	3. It is the initiating player's turn.
	*	4. The current stage is act
	*	5. Both players must be in the same city
	*	6. The card index is a valid city card in the target player's hand
	*	7. The city index of the card in the target player's hand matches his location
	*/
	template<>
	bool ActionHandler::validate<ShareKnowledge>(const ShareKnowledge& a) const{
		if (!(game.stateMachine.playerExists(a.player) &&
			game.stateMachine.playerExists(a.target) &&
			game.stateMachine.playerCanAct(a.player) &&
			game.stateMachine.getPlayer(a.player).getLocation() == 
			game.stateMachine.getPlayer(a.target).getLocation()))
			return false;
		// check the card index validity
		const PlayerBase& p = game.getPlayer(a.target);
		if (a.cardIndex < 0 || a.cardIndex >= p.getCards().size())
			return false;
		// check the card type validity
		const CardBase& card = *p.getCards()[a.cardIndex];
		if (card.type != CardType::City)
			return false;
		// Check the card validity
		return static_cast<const CityCard&>(card).cityIndex == p.getLocation();
	}

	template<>
	bool ActionHandler::execute<ShareKnowledge>(const ShareKnowledge& a){
		if (!a.validate(*this)){
			return false;
		}
		// Remove the card to the discard pile
		PlayerBase& player = game.stateMachine.getPlayer(a.player);
		detail::Deck<CardBasePtr>& cards = player.getCards();
		game.stateMachine.discardPlayerCard(cards[a.index]);
		cards.erase(cards.begin() + a.index);
		// Check if the player has the required number of cards
		game.stateMachine.playerDidAct(a.player, a.getActionType());
		return true;
	}

	template<>
	bool ActionHandler::validate<Outbreak>(const Outbreak& a) const{
		const auto& city = game.stateMachine.getMap()[a.infection.city];
		// If the city does not have 3 cubes of the specified type,
		// the outbreak will not take place
		if (city.getCubes(a.infection.diseaseType) != 3){
			return false;
		} 
		return true;
	}

	template<>
	bool ActionHandler::execute<Outbreak>(const Outbreak& a){
		return outBreakImpl(a, std::set<CityIndex>());
	}


	bool ActionHandler::infectImpl(const Infect& a, std::set<CityIndex>& outbreakedCities)
	{
		if (!a.validate(*this)){
			return false;
		}
		// If the disease was eradicated, simply discard
		if (game.stateMachine.getGameData().diseases[a.diseaseType].getIsEradicated())
			return true;
		auto& city = game.stateMachine.getMap()[a.city];
		std::size_t currentCubes = city.getCubes(a.diseaseType);
		std::size_t canTake = 3 - currentCubes;	
		std::size_t cubesLeft = game.stateMachine.getGameData().diseaseCubes[a.diseaseType];
		std::size_t willTake = std::min(canTake, a.cubes);
		// Add cubes
		game.stateMachine.addDiseaseCubesOfType(a.diseaseType, a.cubes, a.city);
		if (game.isOver())
			return true;
		// Outbreak if there city took less cubes than it should have
		if (willTake < a.cubes){
			Outbreak out(a);
			return outBreakImpl(out, outbreakedCities);
		}
		return true;
	}

	bool ActionHandler::outBreakImpl(const Outbreak& a, std::set<CityIndex>& outbreakedCities)
	{
		if (!a.validate(*this)){
			return false;
		}
		// The current city has already suffered an outbreak due to the same infection
		if (outbreakedCities.find(a.infection.city) != outbreakedCities.end()){
			return true;
		}
		game.stateMachine.increaseOutbreakMarker();
		if (game.isOver())
			return true;
		// Otherwise, infect each neighbor
		Map::ConnectedCityIterator ai, ai_end;
		bool result = true;
		for (boost::tie(ai, ai_end) = game.stateMachine.getMap().connectedCities(a.infection.city);
			ai != ai_end; ++ai){
			// Create a new infection whose target is the neighbor
			Infect infect(*ai, a.infection.diseaseType, 1);
			// Add the currently outbreaked city to the set of outbreaked cities
			// of the new infection
			outbreakedCities.insert(a.infection.city);
			result = result && infectImpl(infect, outbreakedCities);
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
		if (game.stateMachine.getMap()[a.city].getRegion() != a.diseaseType){
			if (a.cubes != 1)
				return false;
		}
		return true;
	}

	template<>
	bool ActionHandler::execute<Infect>(const Infect& a){
		return infectImpl(a, std::set<CityIndex>());
	}

	template<>
	bool ActionHandler::validate<Epidemic>(const Epidemic& a) const{
		return true;
	}

	template<>
	bool ActionHandler::execute<Epidemic>(const Epidemic& a){
		if (!a.validate(*this)){
			return false;
		}
		game.stateMachine.increaseInfectionRateMarker();
		// Infect if possible
		if (!game.stateMachine.getDeckData().infectionDeck.empty()){
			// Get the card and infect
			auto infectionCard = game.stateMachine.drawInfectionDeckBottom();
			Infect infect(infectionCard->cityIndex, game.stateMachine.getMap()[infectionCard->cityIndex].getRegion(), 3);
			infect.execute(*this);
			// Check the game condition. Might have lost prematurely
			if (game.isOver())
				return true;
		}
		game.stateMachine.mergeInfectionDecks();
		return true;
	}
}