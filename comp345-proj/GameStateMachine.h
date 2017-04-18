#pragma once
#include "Data.h"
#include "Map.h"
#include "ActionBase.h"
#include "Notifications.h"
#include "detail\NotificationCenter.h"

namespace pan{
	class Game;

	/**
	*	@brief class represents the state machine of the Game.
	*	Is responsible for switching between game states and keeping the data consistent.
	*	@author Hrachya Hakobyan
	*/
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
		bool operator!=(const GameStateMachine& o) const { return !(*this == o); }

		/**
		*	Attempt to initialize the state machine
		*	@return true if initialization was successful
		*/
		bool initialize();

		/**
		*	Get the current infection rate value
		*	@return the current infection rate value
		*/
		std::size_t getInfectCount() const {return gameData.settings.infectionRates[gameData.infectionRateMarker];}
		/**
		*	Attempt to increase the outbreak marker.
		*	If it is already at the maximum, nothing will happen.
		*	If it reached the maximum due to this call, the game will transition to the state "Defeat"
		*/
		void increaseOutbreakMarker();
		/**
		*	Attempt to increase the infection rate marker.
		*	If it is already at the maximum, nothing will happen.
		*/
		void increaseInfectionRateMarker();

		void setSkipNextInfection(bool skip);

		inline bool getSkipNextInfection() const;

		const PlayerData& getPlayerData() const { return playerData; }
		/**
		*	Check if a player with the specified index exists
		*	@param i the index of the player to check
		*	@return true if the player exists
		*/
		bool playerExists(PlayerIndex i) const { return i >= 0 && i < static_cast<int>(playerData.players.size()); }
		/**
		*	Moves the player to the specified city 
		*	@param i the player index to be moved
		*	@param target the target city
		*/
		void movePlayer(PlayerIndex i, CityIndex target);
		/**
		*	Find out if the specified player is allowed to act.
		*	@param i the index of the player to be checked
		*	@param type the type of the action to be checked against
		*	@return true of the player is allowed to perform an action
		*/
		bool playerCanAct(PlayerIndex i, ActionType type) const;
		/**
		*	Find out if it is the specified player's turn to play
		*	@param i the index of the player to be checked
		*	@return true of it is the player's turn tu play
		*/
		bool isPlayersTurn(PlayerIndex i) const;
		/**
		*	Inform the state machine that the player has performed an action
		*	The state machine will change the state of the game based on the current player stage and the action type.
		*	@param i the index of the player
		*	@param a the action type performed
		*/
		void playerDidAct(PlayerIndex i, ActionType a);

		inline const PlayerBase& getPlayer(PlayerIndex i) const { return *playerData.players[i]; }
		inline PlayerBase& getPlayer(PlayerIndex i) { return *playerData.players[i]; }

		template<Roles R>
		PlayerIndex addPlayer(const std::string& name = "");
		PlayerIndex addRandomPlayer(const std::string& name = "");

		// Deck
		const DeckData& getDeckData() const { return deckData; }
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
		const GameData& getGameData() const { return gameData; }
		bool researchStationsMaxedOut() const { return gameData.researchStations == gameData.settings.maxResearchStations; }
		bool addResearchStation(CityIndex);
		bool allDiseasesAreCured() const;
		bool allDiseasesAreEradicated() const;
		std::size_t countCuredDiseases() const;
		std::size_t countEradicatedDiseases() const;
		void removeDiseaseCubesOfType(DiseaseType, std::size_t, CityIndex city);
		void addDiseaseCubesOfType(DiseaseType, std::size_t, CityIndex city);
		void cureDisease(DiseaseType type);
	

		// Map
		inline const Map& getMap() const { return map; }

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

	bool GameStateMachine::getSkipNextInfection() const
	{
		return gameData.skipNextInfection;
	}

	template<typename T>
	void GameStateMachine::discardPlayerCards(const detail::Deck<T>& cards)
	{
		deckData.playerDiscardDeck.push(cards);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new DeckDataUpdateNotification(deckData)));
	}

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
		PlayerIndex index = static_cast<PlayerIndex>(playerData.players.size());
		auto player = std::shared_ptr<PlayerBase>(new Player<R>(index, name));
		playerData.players.push_back(player);
		detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new PlayerDataUpdateNotification(playerData)));
		return index;
	}
}

