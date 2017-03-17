#include "stdafx.h"
#include "Game.h"
#include "CityCard.h"
#include "EpidemicCard.h"
#include "InfectionCard.h"
#include "EventCard.h"
#include "Infect.h"
#include "FileManager.h"

namespace pan{

	Game::Game(const Settings& s) :
		actionHandler(*this),
		gameData(s)
	{
	}

	Game::Game(const Settings& s, const Map& m) :
		actionHandler(*this),
		gameData(s),
		map(m)
	{
	}

	Game::Game(const Game& o) :
		actionHandler(*this),
		gameData(o.gameData),
		deckData(o.deckData),
		playerData(o.playerData),
		actionData(o.actionData),
		map(o.map)		
	{
	}

	Game::Game(Game&& o) :
		actionHandler(*this),
		gameData(std::move(o.gameData)),
		deckData(std::move(o.deckData)),
		playerData(std::move(o.playerData)),
		actionData(std::move(o.actionData)),
		map(std::move(o.map))
	{
	}

	Game::~Game()
	{

	}

	Game& Game::operator=(const Game& o)
	{
		this->gameData = o.gameData;
		this->deckData = o.deckData;
		this->playerData = o.playerData;
		this->actionData = o.actionData;
		this->map = o.map;
		return *this;
	}

	Game& Game::operator=(Game&& o)
	{
		this->gameData = std::move(o.gameData);
		this->deckData = std::move(o.deckData);
		this->playerData = std::move(o.playerData);
		this->actionData = std::move(o.actionData);
		this->map = std::move(o.map);
		return *this;
	}

	bool Game::operator==(const Game& o) const
	{
		return (this->gameData == o.gameData
			&& this->deckData == o.deckData
			&& this->playerData == o.playerData
			&& this->deckData == o.deckData
			&& this->map == o.map);
	}

	bool Game::initialize()
	{
		if (isInitialized())
			return true;
		// Not enough players
		if (playerData.players.size() < gameData.settings.playerCount)
			return false;

		// Add the diseases based on map regions
		for (auto diseaseType : map.getRegions()){
			gameData.diseases.push_back(Disease(diseaseType));
		}

		// Construct the disease cubes
		for (std::size_t i = 0; i < gameData.diseases.size(); i++){
			gameData.diseaseCubes.push_back(gameData.settings.diseaseCubesPerDisease);
			gameData.removedDiseasesCubes.push_back(0);
		}

		// Fill in player cards
		for (std::size_t i = 0; i < map.numCities(); i++){
			deckData.playerDeck.push(std::shared_ptr<CardBase>(new CityCard(static_cast<CityIndex>(i))));
		}
		for (const auto& event: EventTypeDescriptions){
			deckData.playerDeck.push(std::shared_ptr<CardBase>(new EventCard(event.first)));
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
			temp.push(std::shared_ptr<CardBase>(new EpidemicCard()));
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
		
		// Add the initial research station
		map[0].researchStation = true;
		gameData.researchStations++;
		
		// Move the players to their initial positions
		for (int i = 0; i < static_cast<int>(playerData.players.size()); i++){
			playerData.players[i]->setLocation(0);
			map[0].addPlayer(i);
		}

		// Infect cities
		for (std::size_t cubes = 3; cubes > 0; cubes--){
			for (std::size_t card = 0; card < 3; card++){
				// Get top card
				auto cardPtr = deckData.infectionDeck.top();
				deckData.infectionDeck.pop();
				// The disease type
				DiseaseType type = map.regionForCity(cardPtr->cityIndex);
				// Infect
				Infect infect(cardPtr->cityIndex, type, cubes);
				infect.execute(actionHandler);
				// Add to discard pile
				deckData.infectionDiscardDeck.push(cardPtr);
			}
		}

		// Set the player turn and stage
		playerData.turn = 0;
		playerData.stage = PlayerStage::Act;

		return true;
	}

	std::string Game::description() const
	{
		std::string res = "Game:\n";
		res += "Map: " + map.description() + '\n';
		res += "GameData:\n" + gameData.description() + '\n';
		res += "DeckData:\n" + deckData.description() + '\n';
		res += "PlayerData:\n" + playerData.description() + '\n';
		return res;
	}

	void Game::addAction(const ActionBase& action)
	{
		if (!isInitialized() || isOver())
			return;
		actionData.actionQueue.push(std::unique_ptr<ActionBase>(action.clone()));
	}

	void Game::execute()
	{
		if (!isInitialized() || isOver())
			return;
		if (actionData.actionQueue.empty())
			return;
		auto action = actionData.actionQueue.front();
		actionData.actionQueue.pop();
		// If the action was valid, add it to the completed actions
		if (action->execute(actionHandler))
			actionData.completedActions.push(action);
	}

	void Game::executeAll()
	{
		if (!isInitialized() || isOver())
			return;
		while (actionData.actionQueue.empty())
			execute();
	}

	void Game::changeState(GameState newState)
	{
		if (!isInitialized() || isOver())
			return;
		if (newState != GameState::InProgress){
			gameData.state = newState;
			// Clear all pending actions
			actionData.actionQueue = {};
		}
	}

	bool Game::save(const std::string& name) const
	{
		return FileManager::getInstance().save(*this, name, "save");
	}

	bool Game::load(const std::string& name, Game& game)
	{
		return FileManager::getInstance().load(game, name, "save");
	}
}