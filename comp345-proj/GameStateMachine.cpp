#include "stdafx.h"
#include "GameStateMachine.h"
#include "Cards.h"
#include "Actions.h"
#include "Game.h"

namespace pan{
	GameStateMachine::GameStateMachine()
	{
	}

	GameStateMachine::GameStateMachine(const Settings& s) :
	gameData(s)
	{
	}

	GameStateMachine::GameStateMachine(const Settings& s, const Map& m) :
	gameData(s),
	map(m)
	{
	}

	GameStateMachine::GameStateMachine(const GameStateMachine& o) :
		gameData(o.gameData),
		deckData(o.deckData),
		playerData(o.playerData),
		map(o.map)
	{
	}

	GameStateMachine::GameStateMachine(GameStateMachine&& o) :
		gameData(std::move(o.gameData)),
		deckData(std::move(o.deckData)),
		playerData(std::move(o.playerData)),
		map(std::move(o.map))
	{
	}

	GameStateMachine::~GameStateMachine()
	{

	}

	GameStateMachine& GameStateMachine::operator=(const GameStateMachine& o)
	{
		this->gameData = o.gameData;
		this->deckData = o.deckData;
		this->playerData = o.playerData;
		this->map = o.map;
		return *this;
	}

	GameStateMachine& GameStateMachine::operator=(GameStateMachine&& o)
	{
		this->gameData = std::move(o.gameData);
		this->deckData = std::move(o.deckData);
		this->playerData = std::move(o.playerData);
		this->map = std::move(o.map);
		return *this;
	}

	bool GameStateMachine::operator==(const GameStateMachine& o) const
	{
		return (this->gameData == o.gameData
			&& this->deckData == o.deckData
			&& this->playerData == o.playerData
			&& this->map == o.map);
	}

	std::string GameStateMachine::description() const
	{
		std::string res = "Game State:\n";
		res += "Map: " + map.description() + '\n';
		res += "GameData:\n" + gameData.description() + '\n';
		res += "DeckData:\n" + deckData.description() + '\n';
		res += "PlayerData:\n" + playerData.description() + '\n';
		return res;
	}

	bool GameStateMachine::initialize()
	{
		if (gameData.initialized)
			return true;
		// Not enough players
		if (playerData.players.size() < gameData.settings.playerCount)
			return false;
		initDiseases();
		initCards();
		initPlayers();
		gameData.initialized = true;
		return true;
	}

	void GameStateMachine::initDiseases()
	{
		// Add the diseases based on map regions
		for (auto diseaseType : map.getRegions()){
			gameData.diseases.push_back(Disease(diseaseType));
		}

		// Construct the disease cubes
		for (std::size_t i = 0; i < gameData.diseases.size(); i++){
			gameData.diseaseCubes.push_back(gameData.settings.diseaseCubesPerDisease);
			gameData.removedDiseasesCubes.push_back(0);
		}
	}

	void GameStateMachine::initCards()
	{
		// Fill in player cards
		Map::CityIndexIterator ci, ci_end;
		for (boost::tie(ci, ci_end) = map.cities(); ci != ci_end; ++ci){
			deckData.playerDeck.push(CardBasePtr(new CityCard(*ci, map[*ci].getRegion())));
		}

		for (const auto& event : EventTypeDescriptions){
			deckData.playerDeck.push(CardBasePtr(new EventCard(event.first)));
		}
		srand(static_cast<unsigned int>(time(NULL)));
		deckData.playerDeck.shuffle();

		// Deal player cards
		// Iterare each player, and deal from player deck according to the draw size
		for (auto& player : playerData.players){
			player->setCards(deckData.playerDeck.deal(gameData.settings.initialCards));
		}

		// Add epidemic cards and shuffle
		auto tempPlayerCards = std::move(deckData.playerDeck);
		std::size_t chunkSize = static_cast<std::size_t>(std::ceil(double(tempPlayerCards.size()) / gameData.settings.epidemicCardCount));
		for (std::size_t i = 0; i < gameData.settings.epidemicCardCount; i++){
			auto temp = tempPlayerCards.deal(chunkSize);
			temp.push(CardBasePtr(new EpidemicCard()));
			temp.shuffle();
			deckData.playerDeck.push(std::move(temp));
		}
#ifdef _DEBUG
		assert(tempPlayerCards.empty() && "Cards not dealt correctly");
#endif

		// Add infection cards
		for (std::size_t i = 0; i < map.numCities(); i++){
			deckData.infectionDeck.push(std::shared_ptr<InfectionCard>(new InfectionCard(static_cast<CityIndex>(i))));
		}
		srand(static_cast<unsigned int>(time(NULL)));
		deckData.infectionDeck.shuffle();
	}

	void GameStateMachine::initPlayers()
	{
		// Add the initial research station
		map[0].researchStation = true;
		gameData.researchStations++;

		// Move the players to their initial positions
		for (int i = 0; i < static_cast<int>(playerData.players.size()); i++){
			playerData.players[i]->setLocation(0);
			map[0].addPlayer(playerData.players[i]);
		}
		// Set the player turn and stage
		playerData.turn = 0;
		playerData.stage = PlayerStage::Act;
		playerData.actionCounter = 0;
	}

	PlayerIndex GameStateMachine::addRandomPlayer(const std::string& name)
	{
		if (playerData.players.size() >= gameData.settings.playerCount)
			return InvalidPlayerIndex;
		std::vector<Roles> validRoles;
		for (unsigned int i = 0; i < playerData.occupiedRoles.size(); i++){
			if (!playerData.occupiedRoles[i]) validRoles.push_back(static_cast<Roles>(i));
		}
		if (validRoles.empty()) return InvalidPlayerIndex;
		srand(static_cast<unsigned int>(time(NULL)));
		Roles role = validRoles[(rand() % (int)(validRoles.size()))];
		playerData.occupiedRoles[static_cast<std::underlying_type<Roles>::type>(role)] = true;
		PlayerIndex index = static_cast<PlayerIndex>(playerData.players.size());
		playerData.players.push_back(player(role, index, name));
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new PlayerDataUpdateNotification(playerData)));
		return index;
	}

	void GameStateMachine::increaseInfectionRateMarker()
	{
		// If already maxed out
		if (gameData.infectionRateMarker == gameData.settings.infectionRates.size() - 1){
			return;
		}
		gameData.infectionRateMarker++;
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new GameDataUpdateNotification(gameData)));
	}

	void GameStateMachine::increaseOutbreakMarker()
	{
		// If already maxed out
		if (gameData.outbreakMarker == gameData.settings.outbreakMarkerMax){
			return;
		}
		gameData.outbreakMarker++;
		if (gameData.outbreakMarker == gameData.settings.outbreakMarkerMax){
			setGameState(GameState::Defeat);
		}
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new GameDataUpdateNotification(gameData)));
	}

	detail::Deck<CardBasePtr> GameStateMachine::drawPlayerDeckTop(std::size_t count)
	{
		// If there are not enough cards to draw from the player deck the game is lost
		if (deckData.playerDeck.size() < count){
			setGameState(GameState::Defeat);
			return detail::Deck<CardBasePtr>();
		}
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new DeckDataUpdateNotification(deckData)));
		return deckData.playerDeck.deal(count);
	}

	std::shared_ptr<InfectionCard> GameStateMachine::drawInfectionDeckTop()
	{
		if (deckData.infectionDeck.empty())
			return nullptr;
		auto card = deckData.infectionDeck.top();
		deckData.infectionDeck.pop();
		deckData.infectionDiscardDeck.push(card);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new DeckDataUpdateNotification(deckData)));
		return card;
	}

	std::shared_ptr<InfectionCard> GameStateMachine::drawInfectionDeckBottom()
	{
		if (deckData.infectionDeck.empty())
			return nullptr;
		auto card = deckData.infectionDeck.bottom();
		deckData.infectionDeck.pop_bottom();
		deckData.infectionDiscardDeck.push(card);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new DeckDataUpdateNotification(deckData)));
		return card;
	}

	void GameStateMachine::discardPlayerCard(CardBasePtr card)
	{
		deckData.playerDiscardDeck.push(card);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new DeckDataUpdateNotification(deckData)));
	}

	detail::Deck<std::shared_ptr<InfectionCard>> GameStateMachine::drawInfectionDeckTop(std::size_t count)
	{
		auto cards = deckData.infectionDeck.deal(count);
		deckData.infectionDiscardDeck.push(cards);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new DeckDataUpdateNotification(deckData)));
		return cards;
	}

	void GameStateMachine::mergeInfectionDecks()
	{
		auto discardedCards = std::move(deckData.infectionDiscardDeck);
		srand(static_cast<unsigned int>(time(NULL)));
		discardedCards.shuffle();
		deckData.infectionDeck.push(discardedCards);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new DeckDataUpdateNotification(deckData)));
	}

	void GameStateMachine::cureDisease(DiseaseType type)
	{
		gameData.diseases[type].setIsCured(true);
		// Check if the disease is eradicated
		if (gameData.removedDiseasesCubes[type] == gameData.settings.diseaseCubesPerDisease)
			gameData.diseases[type].setIsEradicated(true);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new GameDataUpdateNotification(gameData)));
	}

	void GameStateMachine::removeDiseaseCubesOfType(DiseaseType type, std::size_t toRemove, CityIndex cIndex)
	{
		auto& city = map[cIndex];
		std::size_t cityCubes = city.getCubes(type);
		std::size_t willRemove = std::min(cityCubes, toRemove);
		// Take cubes from the city
		city.setCubes(type, cityCubes - willRemove);
		// Add the cubes to the removed cubes 
		gameData.removedDiseasesCubes[type] += willRemove;
		bool isCured = gameData.diseases[type].getIsCured();
		// Check if the disease was eradicated
		if (isCured && gameData.removedDiseasesCubes[type] ==
			gameData.settings.diseaseCubesPerDisease){
			gameData.diseases[type].setIsEradicated(true);
		}
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new GameDataUpdateNotification(gameData)));
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new CityUpdateNotification(city, cIndex)));
	}

	void GameStateMachine::addDiseaseCubesOfType(DiseaseType type, std::size_t toAdd, CityIndex cIndex)
	{
		// Get the city reference
		auto& city = map[cIndex];
		// The current cubes of the city of the givem diseaseType
		std::size_t currentCubes = city.getCubes(type);
		// How many more the city is able to take
		std::size_t canTake = 3 - currentCubes;
		// How many cubes are left in the game
		std::size_t cubesLeft = gameData.diseaseCubes[type];
		// How many the city will actually take
		// The minimum of how many it can actually take, and how many it is required to take
		std::size_t willTake = std::min(canTake, toAdd);
		// If there are less cubes left than the city will actually take
		// automatically the game is lost.
		if (willTake > cubesLeft){
			setGameState(GameState::Defeat);
			detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new GameDataUpdateNotification(gameData)));
			return;
		}
		// Take cubes from the city
		city.setCubes(type, currentCubes + willTake);
		// Add the cubes to the removed cubes 
		gameData.diseaseCubes[type] -= willTake;
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new CityUpdateNotification(city, cIndex)));
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new GameDataUpdateNotification(gameData)));
	}

	void GameStateMachine::setGameState(GameState state)
	{
		// If the game is not initialized or the game is already finished
		// or if the game attempts to transition back to InProgress state
		if (!gameData.initialized || gameData.state != GameState::InProgress
			|| state == GameState::InProgress)
			return;
		gameData.state = state;
	}

	bool GameStateMachine::addResearchStation(CityIndex city)
	{
		if (researchStationsMaxedOut())
			return false;
		if (map[city].researchStation)
			return false;
		map[city].researchStation = true;
		gameData.researchStations++;
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new CityUpdateNotification(map[city], city)));
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new GameDataUpdateNotification(gameData)));
		return true;
	}

#pragma message("Add validations")
	void GameStateMachine::setPlayerStage(PlayerStage stage)
	{
		playerData.prevStage = playerData.stage;
		playerData.stage = stage;
	}

	void GameStateMachine::playerDidAct(PlayerIndex index, ActionType type)
	{
		// The stage is Draw and the action is Draw action
		if (playerData.stage == PlayerStage::Draw && type == ActionType::Draw){
			if (playerData.players[index]->getCards().size() > gameData.settings.playerHandMax)
				setPlayerStage(PlayerStage::Discard);
			else
				setPlayerStage(PlayerStage::Infect);
		}
		// The stage is Act and the action is of regular type
		else if (playerData.stage == PlayerStage::Act && isRegular(type)){
			// Increment the action counter
			playerData.actionCounter = (playerData.actionCounter + 1) % 4;
			// If the player has more cards than required, change to discard stage
			if (playerData.players[index]->getCards().size() > gameData.settings.playerHandMax)
				setPlayerStage(PlayerStage::Discard);
			else if (playerData.actionCounter == 0){
				setPlayerStage(PlayerStage::Draw);
			}
		}
		// We can go back to Act stage only from infect
		else if (type == ActionType::Infect){
			playerData.turn = (playerData.turn + 1) % playerData.players.size();
			setPlayerStage(PlayerStage::Act);
		}
		else if (type == ActionType::Discard){
			// Can switch the state only if the player has less
			// than the maximum allowed number of cards
			if (playerData.players[index]->getCards().size() <= gameData.settings.playerHandMax){
				// The previous stage was act
				if (playerData.prevStage == PlayerStage::Act){
					// The last action performed by the player forced to discard a card (e.g. Share Knowledge)
					if (playerData.actionCounter == 0){
						setPlayerStage(PlayerStage::Draw);
					}
					// The player has still actions to do
					else {
						setPlayerStage(PlayerStage::Act);
					}
				}
				else {
					// The player has to infect
					setPlayerStage(PlayerStage::Infect);
				}
			}
		}
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new PlayerDataUpdateNotification(playerData)));
	}

	bool GameStateMachine::isPlayersTurn(PlayerIndex i) const
	{
		return playerData.turn == i;
	}

	bool GameStateMachine::playerCanAct(PlayerIndex i, ActionType type) const
	{
		// If it is not the player's turn or the game is not in progress
		// the player cannot act
		if (!isPlayersTurn(i) || gameData.state != GameState::InProgress)
			return false;
		// If the player is in act state, check the action counter
		if (playerData.stage == PlayerStage::Act && isRegular(type))
			return playerData.actionCounter < 4;
		// If the stage is discard, the player can act only if he has more then max cards
		if (playerData.stage == PlayerStage::Discard && type == ActionType::Discard)
			return (playerData.players[i]->getCards().size() > gameData.settings.playerHandMax);
		// If the stage is infect
		if (playerData.stage == PlayerStage::Infect && type == ActionType::Infect)
			return true;
		// If the stage is draw
		if (playerData.stage == PlayerStage::Draw && type == ActionType::Draw)
			return true;
		// False otherwise
		return false;
	}

	void GameStateMachine::movePlayer(PlayerIndex player, CityIndex target){
		PlayerBase& playerRef = getPlayer(player);
		// Remove from previous city
		CityIndex oldLocation = playerRef.getLocation();
		map[oldLocation].removePlayer(playerData.players[player]);
		// Add to the target city
		map[target].addPlayer(playerData.players[player]);
		// Update the player's location
		playerRef.setLocation(target);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new PlayerUpdateNotification(playerRef)));
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new CityUpdateNotification(map[oldLocation], oldLocation)));
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new CityUpdateNotification(map[target], target)));
	}
}