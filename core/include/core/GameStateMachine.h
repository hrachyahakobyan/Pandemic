#pragma once
#include "Data.h"
#include "Map.h"
#include "ActionBase.h"

namespace pan{
	class Game;

	class GameStateMachine
	{
	public:
		static const int InvalidPlayerIndex = -1;
		GameStateMachine();
		GameStateMachine(const Settings&);
		GameStateMachine(const Settings& s, const Map& m);
		GameStateMachine(const GameStateMachine&);
		GameStateMachine(GameStateMachine&&);
		GameStateMachine& operator=(const GameStateMachine&);
		GameStateMachine& operator=(GameStateMachine&& o);
		~GameStateMachine();

		std::string description() const;

		bool operator==(const GameStateMachine&) const;
		inline bool operator!=(const GameStateMachine&) const;
		bool initialize();

		// Game
		std::size_t getInfectCount() const {return gameData.settings.infectionRates[gameData.infectionRateMarker];}
		void increaseOutbreakMarker();
		void increaseInfectionRateMarker();

		// Players
		inline const PlayerData& getPlayerData() const;
		inline bool playerExists(PlayerIndex i) const;
		void movePlayer(PlayerIndex i, CityIndex target);
		bool playerCanAct(PlayerIndex) const;
		bool isPlayersTurn(PlayerIndex) const;
		void playerDidAct(PlayerIndex, ActionType);

		const PlayerBase& getPlayer(PlayerIndex i) const;
		PlayerBase& getPlayer(PlayerIndex i);

		template<Roles R>
		PlayerIndex addPlayer(const std::string& name = "");
		PlayerIndex addRandomPlayer(const std::string& name = "");

		// Deck
		inline const DeckData& getDeckData() const;
		CardBasePtr drawPlayerDeckTop();
		detail::Deck<CardBasePtr> drawPlayerDeckTop(std::size_t);
		std::shared_ptr<InfectionCard> drawInfectionDeckTop();
		detail::Deck<std::shared_ptr<InfectionCard>> drawInfectionDeckTop(std::size_t);
		std::shared_ptr<InfectionCard> drawInfectionDeckBottom();
		void discardPlayerCard(CardBasePtr);
		template<typename T>
		void discardPlayerCards(const detail::Deck<T>&);
		void mergeInfectionDecks();

		// GameStateMachine Data
		inline const GameData& getGameData() const;
		bool researchStationsMaxedOut() const;
		bool addResearchStation(CityIndex);
		bool allDiseasesAreCured() const;
		bool allDiseasesAreEradicated() const;
		std::size_t countCuredDiseases() const;
		std::size_t countEradicatedDiseases() const;
		void removeDiseaseCubesOfType(DiseaseType, std::size_t, CityIndex city);
		void addDiseaseCubesOfType(DiseaseType, std::size_t, CityIndex city);
		void cureDisease(DiseaseType type);
	

		// Map
		inline const Map& getMap() const;

	private:
		GameData gameData;
		DeckData deckData;
		PlayerData playerData;
		Map map;

		void initDiseases();
		void initCards();
		void initPlayers();

		void setGameState(GameState state);
		void setPlayerStage(PlayerStage stage);

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_NVP(map);
			ar & BOOST_SERIALIZATION_NVP(playerData);
			ar & BOOST_SERIALIZATION_NVP(gameData);
			ar & BOOST_SERIALIZATION_NVP(deckData);
		}

#ifdef _DEBUG
#ifndef DISABLE_TESTS
		FRIEND_TESTS
#endif
#endif
	};


	template<Roles R>
	PlayerIndex GameStateMachine::addPlayer(const std::string& name)
	{
		// Maximum number of players exceeded
		if (playerData.players.size() >= gameData.settings.playerCount)
			return InvalidPlayerIndex;
		// If the role is occupied
		if (playerData.occupiedRoles[static_cast<std::underlying_type<Roles>::type>(R)])
			return InvalidPlayerIndex;
		playerData.occupiedRoles[static_cast<std::underlying_type<Roles>::type>(R)] = true;
		auto player = std::shared_ptr<PlayerBase>(new Player<R>(name));
		playerData.players.push_back(player);
		return static_cast<PlayerIndex>(playerData.players.size() - 1);
	}
}

