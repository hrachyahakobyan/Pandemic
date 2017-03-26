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
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player) ||
			!playerCanAct(m.player)){
			return false;
		}
		// Check if the player is already in the target city
		const auto& player = game.getPlayer(m.player);
		if (player.getLocation() == m.targetCity){
			return false;
		}
		// Check if the destination is a neighbor of the players location
		return game.map.connectionExists(m.targetCity, player.getLocation());
	}

	template<>
	bool ActionHandler::execute<Move>(const Move& m){
		if (!m.validate(*this)){
			return false;
		}
		moveImpl(m.player, m.targetCity);
		commitAction(m.player);
		return true;
	}

	template<>
	bool ActionHandler::validate<DirectFlight>(const DirectFlight& m) const{
		// Check if parameters are valid
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player) || 
			!playerCanAct(m.player)){
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
		PlayerBase& player = game.getPlayer(m.player);
		// Remove the city card and put into discard pile
		std::shared_ptr<CardBase> cardToRemove = player.removeCityCard(m.targetCity);
		game.deckData.playerDiscardDeck.push(cardToRemove);
		moveImpl(m.player, m.targetCity);
		commitAction(m.player);
		return true;
	}

	template<>
	bool ActionHandler::validate<CharterFlight>(const CharterFlight& m) const{
		// Check if parameters are valid
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player) ||
			!playerCanAct(m.player)){
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
		PlayerBase& player = game.getPlayer(m.player);
		// Remove the city card and put it in the discard pile
		std::shared_ptr<CardBase> cardToRemove = player.removeCityCard(player.getLocation());
		game.deckData.playerDiscardDeck.push(cardToRemove);
		// Move the player
		moveImpl(m.player, m.targetCity);
		commitAction(m.player);
		return true;
	}

	template<>
	bool ActionHandler::validate<ShuttleFlight>(const ShuttleFlight& m) const{
		// Check if parameters are valid
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.player) ||
			!playerCanAct(m.player)){
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
	bool ActionHandler::execute<ShuttleFlight>(const ShuttleFlight& m){
		if (!m.validate(*this)){
			return false;
		}
		moveImpl(m.player, m.targetCity);
		commitAction(m.player);
		return true;
	}

	template<>
	bool ActionHandler::validate<BuildResearchStation>(const BuildResearchStation& m) const{
		// Check if parameters are valid
		if (!game.playerExists(m.player)
			|| !playerCanAct(m.player)){
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
		return player.hasCityCard(player.getLocation());
	}

	template<>
	bool ActionHandler::execute<BuildResearchStation>(const BuildResearchStation& m){
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.player);
		std::shared_ptr<CardBase> cardToRemove = player.removeCityCard(player.getLocation());
		game.deckData.playerDiscardDeck.push(cardToRemove);
		// add research station to the city
		game.map[player.getLocation()].researchStation = true;
		// Increment research stations
		game.gameData.researchStations++;
		commitAction(m.player);
		return true;
	}

#pragma message("Validate disease type parameter")
	template<>
	bool ActionHandler::validate<TreatDisease>(const TreatDisease& m) const{
		// Check if parameters are valid
		if (!game.playerExists(m.player) ||
			!playerCanAct(m.player)){
			return false;
		}
		const PlayerBase& player = game.getPlayer(m.player);
		// Check if the city the player is in has a disease cube
		// of the specified type
		std::size_t cityCubes = game.map[player.getLocation()].getCubes(m.diseaseType);
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
		auto& city = game.map[player.getLocation()];
		std::size_t cityCubes = city.getCubes(m.diseaseType);
		// whether the disease is cured
		bool isCured = game.gameData.diseases[m.diseaseType].getIsCured();
		// If the disease is cured, remove all cubes of the specified type
		std::size_t toRemove = (isCured ? cityCubes : 1);
		// Remove cubes from the city
		city.setCubes(m.diseaseType, cityCubes - toRemove);
		// Add the cubes to the removed cubes 
		game.gameData.removedDiseasesCubes[m.diseaseType] += toRemove;

		// Check if the disease was eradicated
		if (isCured && game.gameData.removedDiseasesCubes[m.diseaseType] ==
			game.gameData.settings.diseaseCubesPerDisease){
			game.gameData.diseases[m.diseaseType].setIsEradicated(true);
		}

		// Check if all diseases have been cured
		bool allCured = true;
		for (const auto& d : game.gameData.diseases){
			allCured = allCured && d.getIsCured();
		}
		// Victory!
		if (allCured){
			game.changeState(GameState::Victory);
		}
		commitAction(m.player);
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
		if (!game.playerExists(m.player) ||
			!playerCanAct(m.player)){
			return false;
		}
		// Check if the disease is already cured
		if (game.gameData.diseases[m.diseaseType].getIsCured())
			return false;
		// Check if has a research station
		const PlayerBase& p = game.getPlayer(m.player);
		if (!game.map[p.getLocation()].researchStation)
			return false;
		return p.countCardsMatchingRegion(m.diseaseType) >= game.gameData.settings.discoverCureCardCount;
	}

	template<>
	bool ActionHandler::execute<DiscoverCure>(const DiscoverCure& m){
		if (!m.validate(*this)){
			return false;
		}
		PlayerBase& p = game.getPlayer(m.player);
		auto removedCards = p.removeCardsMatchingRegion(m.diseaseType, game.gameData.settings.discoverCureCardCount);
		game.deckData.playerDiscardDeck.push(removedCards);
		// cure the disease
		game.gameData.diseases[m.diseaseType].setIsCured(true);
		// check if we eradicated the disease
		if (game.gameData.removedDiseasesCubes[m.diseaseType] == game.gameData.settings.diseaseCubesPerDisease)
			game.gameData.diseases[m.diseaseType].setIsEradicated(true);
		commitAction(m.player);
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
		return (game.playerExists(a.player) && 
			    isPlayersTurn(a.player) &&
				game.playerData.stage == PlayerStage::Draw);
	}

	template<>
	bool ActionHandler::execute<DrawPlayerCards>(const DrawPlayerCards& a){
		if (!a.validate(*this)){
			return false;
		}
		// If there are not enough player cards, the game is lot
		if (game.deckData.playerDeck.size() < game.gameData.settings.playerDrawCount){
			game.changeState(GameState::Defeat);
			return true;
		}
		auto& player = game.getPlayer(a.player);
		for (std::size_t i = 0; i < game.gameData.settings.playerDrawCount; i++){
			auto card = game.deckData.playerDeck.top();
			game.deckData.playerDeck.pop();
			// Epidemic card, resolve
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
		// If the player ends up having more cards than he/she must
		// the next stage is set to Discard.
		// Otherwise, the next stage is Infect
		if (player.getCards().size() > game.gameData.settings.playerHandMax){
			game.playerData.stage = PlayerStage::Discard;
		} else {
			game.playerData.stage = PlayerStage::Infect;
		}
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
		return (game.playerExists(a.player) &&
			isPlayersTurn(a.player) &&
			game.playerData.stage == PlayerStage::Infect);
	}

	template<>
	bool ActionHandler::execute<PlayerInfect>(const PlayerInfect& a){
		if (!a.validate(*this)){
			return false;
		}
		// How many infection cards should be drawn
		std::size_t shouldInfect = game.gameData.settings.infectionRates[game.gameData.infectionRateMarker];
		// How many can actually be drawn
		std::size_t actualInfect = std::min(shouldInfect, game.deckData.infectionDeck.size());
		for (std::size_t i = 0; i < actualInfect; i++){
			auto infCard = game.deckData.infectionDeck.top();
			game.deckData.infectionDeck.pop();
			game.deckData.infectionDiscardDeck.push(infCard);
			Infect inf(infCard->cityIndex, game.map[infCard->cityIndex].getRegion(), 1);
			inf.execute(*this);
			// Check for game over condition
			// No point to continue
			if (game.isOver())
				return true;
		}
		// Change the player's turn and the stage
		game.playerData.turn = (game.playerData.turn + 1) % game.playerCount();
		game.playerData.stage = PlayerStage::Act;
		// Save the game state
#pragma message("Change this...")
		game.save("build1demo");
		return true;
	}

	/**
	*	@brief validates DiscardCard action
	*	The action is valid if the following hold.
	*	1. The initiating player exists.
	*	2. It is the initiating player's turn.
	*	3. The current stage is Discard.
	*	4. The index is a valid card in the players hand.
	*/
	template<>
	bool ActionHandler::validate<DiscardCard>(const DiscardCard& a) const{
		if (!(game.playerExists(a.player) &&
			isPlayersTurn(a.player) &&
			game.playerData.stage == PlayerStage::Discard))
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
		auto& player = game.getPlayer(a.player);
		auto& cards = player.getCards();
		game.deckData.playerDiscardDeck.push(cards[a.index]);
		cards.erase(cards.begin() + a.index);
		// Check if the player has the required number of cards
		if (cards.size() == game.gameData.settings.playerHandMax)
			game.playerData.stage = PlayerStage::Infect;
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
	bool ActionHandler::execute<Outbreak>(const Outbreak& a){
		return outBreakImpl(a, std::set<CityIndex>());
	}


	bool ActionHandler::infectImpl(const Infect& a, std::set<CityIndex>& outbreakedCities)
	{
		if (!a.validate(*this)){
			return false;
		}
		// If the disease was eradicated, simple discard
		if (game.gameData.diseases[a.diseaseType].getIsEradicated())
			return true;

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
			game.changeState(GameState::Defeat);
			return true;
		}
		// Otherwise, increase the number of cubes in the city
		city.setCubes(a.diseaseType, currentCubes + willTake);
		// And decrease from cubes left
		game.gameData.diseaseCubes[a.diseaseType] = cubesLeft - willTake;

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
		// Check the outbreak marker
		// If it is on max, the game is lost
		if (game.gameData.outbreakMarker == game.gameData.settings.outbreakMarkerMax){
			game.changeState(GameState::Defeat);
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
		if (game.map[a.city].getRegion() != a.diseaseType){
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
		// Increase the infection rate if possible
		if (game.gameData.infectionRateMarker + 1 < game.gameData.settings.infectionRates.size()){
			game.gameData.infectionRateMarker++;
		}
		// Infect if possible
		if (!game.deckData.infectionDeck.empty()){
			// Get the card and infect
			auto infectionCard = game.deckData.infectionDeck.bottom();
			game.deckData.infectionDeck.pop_bottom();
			Infect infect(infectionCard->cityIndex, game.map[infectionCard->cityIndex].getRegion(), 3);
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

	bool ActionHandler::isPlayersTurn(PlayerIndex i) const
	{
		return game.playerData.turn == i;
	}

	bool ActionHandler::playerCanAct(PlayerIndex i) const
	{
		return isPlayersTurn(i) && game.playerData.stage == PlayerStage::Act && game.playerData.actionCounter < 4;
	}

	void ActionHandler::commitAction(PlayerIndex i)
	{
		if (isPlayersTurn(i) && game.playerData.stage == PlayerStage::Act) {
			game.playerData.actionCounter = (game.playerData.actionCounter + 1) % 4;
			if (game.playerData.actionCounter == 0){
				game.playerData.stage = PlayerStage::Draw;
			}
		}
	}

	void ActionHandler::moveImpl(PlayerIndex player, CityIndex target){
		PlayerBase& playerRef = game.getPlayer(player);
		// Remove from previous city
		game.map[playerRef.getLocation()].removePlayer(player);
		// Add to the target city
		game.map[target].addPlayer(player);
		// Update the player's location
		playerRef.setLocation(target);
	}
}