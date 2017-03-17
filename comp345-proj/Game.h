#pragma once
#include "Map.h"
#include "Data.h"
#include "ActionBase.h"
#include "ActionHandler.h"

namespace pan
{
	/**
	*	@brief Game entity which is responsible for
	*	connecting different pieces of the game logic together.
	*	@author Hrachya Hakobyan
	*/
	class Game : public Object
	{
	public:
		static const int InvalidPlayerIndex = -1;

		Game(const Settings& s = Settings::Beginner(2));
		Game(const Settings& s, const Map& m);
		Game(const Game&);
		Game(Game&&);
		Game& operator=(const Game&);
		Game& operator=(Game&& o);
		~Game();

		/**
		*	load a game from a file.
		*	@param file the save file
		*	@param game the object to where the game will be loaded
		*	@return true if the load was successful.
		*/
		static bool load(const std::string& file, Game& game);

		bool operator==(const Game&) const;
		inline bool operator!=(const Game&) const;

		/**
		*	@brief attempt to initialize the game.
		*	The game will be initialized only once.
		*	The game will be initialized if all preconditions are met,
		*	e.g. the game has the required number of players and/or any other precondition.
		*	@return true if the game successfully initialzed, false otherwise
		*/
		bool initialize();
		inline bool isInitialized() const;	

		/**
		*	@brief whether the game is over.
		*	The game is over if the status is either Victory or Defeat
		*/
		inline bool isOver() const;
		/**
		*	@brief get the current state of the game.
		*	The game can either be running, or over.
		*	A game that is over either has a state of Victory or Defeat
		*	@return the current state of the game
		*/
		inline GameState getState() const;

		inline const Map& getMap() const;
		inline const GameData& getGameData() const;
		inline const PlayerData& getPlayerData() const;
		inline const DeckData& getDeckData() const;
		std::string description() const;

		/**
		*	Get the current number of players
		*	@return the current number of players
		*/
		inline std::size_t playerCount() const;

		/**
		*	The the player at the specified index
		*	@param index of the player
		*	@return const reference to the player
		*	@throws out_of_range if the index is invalid
		*/
		inline const PlayerBase& getPlayer(PlayerIndex i) const;

		/**
		*	Whether a player with the given index exists
		*	@param index index of the player
		*	@return true if the player exists, false otherwise
		*/
		inline bool playerExists(PlayerIndex i) const;

		/**
		*	@brief Adds a new action to the action queue
		*	If the game is not initialized or is over, the method will have no effect.
		*	@param action the action to be added.
		*/
		void addAction(const ActionBase& action);

		/**
		*	@brief Executes actions in the action queue.
		*	If the game is not initialized or is over, the method will have no effect.
		*	If the action is invalid, it will be removed from the action queue.
		*	If there are no action, the method will have no effect.
		*/
		void execute();

		/**
		*	@brief Executes all actions in the action queue.
		*	If the game is not initialized or is over, the method will have no effect.
		*	If there are no action, the method will have no effect.
		*/
		void executeAll();

		/**
		*	Adds a new player with the specified role.
		*	If the maximum number of players is reached, or if a player with 
		*	the role already exists, will return InvalidPlayerIndex
		*	@param template parameter R denotes the role of the player.
		*	@param name the name of the new player
		*	@return a unique index for the newly created players
		*/
		template<Roles R>
		PlayerIndex addPlayer(const std::string& name = "");

		/**
		*	Adds a new player with a random role.
		*	If all roles are occupied or if the maximum number of players is reached
		*	will return InvalidPlayerIndex
		*	@param name of the player
		*	@return a unique index for the newly created players
		*/
		PlayerIndex addRandomPlayer(const std::string& name = "");

		/**
		*	Saves the game with given a save file name
		*	@param name the name under which to save the game
		*	@return true if the save was successful
		*/
		bool save(const std::string& name) const;

	private:
		struct ActionData{
			// Holds the pending actions
			std::queue<std::shared_ptr<ActionBase>> actionQueue;
			// Holds the completed action. The top actions is the most recent action.
			std::stack<std::shared_ptr<ActionBase>> completedActions;
		};
	private:
		Map map;
		ActionHandler actionHandler;
		DeckData deckData;
		PlayerData playerData;
		GameData gameData;
		ActionData actionData;
		friend class ActionHandler;
	private:
		/* Private Interface */
		/**
		*	@brief returns the player at index
		*	@param i the index of the player to return
		*	@return a reference to the underlying player object
		*/
		inline PlayerBase& getPlayer(PlayerIndex i);

		/**
		*	@brief attempt to alter the state of the game
		*	The games state can be changed from inProgress to Either Defeat or Victory
		*	but not the other way
		*	@param newState the new state of the game
		*/
		void changeState(GameState newState);

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object);
			ar & BOOST_SERIALIZATION_NVP(map);
			ar & BOOST_SERIALIZATION_NVP(playerData);
			ar & BOOST_SERIALIZATION_NVP(gameData);
			ar & BOOST_SERIALIZATION_NVP(deckData);
		}

#ifdef _DEBUG
#ifndef DISABLE_TESTS
		friend class GameTest;
		friend class ActionTest;
		FRIEND_TEST(GameTest, addsPlayers);
		FRIEND_TEST(GameTest, serializes);
		FRIEND_TEST(GameTest, validates);
		FRIEND_TEST(GameTest, executes);
		FRIEND_TEST(GameTest, initializes);
		FRIEND_TEST(ActionTest, Infect);
		FRIEND_TEST(ActionTest, Outbreak);
		FRIEND_TEST(ActionTest, Move);
		FRIEND_TEST(ActionTest, CharterFlight);
		FRIEND_TEST(ActionTest, ShuttleFlight);
		FRIEND_TEST(ActionTest, DirectFlight);
		FRIEND_TEST(ActionTest, BuildResearchStation);
		FRIEND_TEST(OutbreakTest, Test1);
#endif
#endif
	};

	std::size_t Game::playerCount() const
	{
		return playerData.players.size();
	}

	bool Game::operator!=(const Game& o) const
	{
		return !((*this) == o);
	}

	bool Game::isInitialized() const
	{
		return gameData.initialized;
	}

	bool Game::isOver() const
	{
		return gameData.state != GameState::InProgress;
	}

	GameState Game::getState() const
	{
		return gameData.state;
	}

	const Map& Game::getMap() const
	{
		return map;
	}

	const PlayerData& Game::getPlayerData() const
	{
		return playerData;
	}

	const GameData& Game::getGameData() const
	{
		return gameData;
	}

	const DeckData& Game::getDeckData() const
	{
		return deckData;
	}

	template<Roles R>
	PlayerIndex Game::addPlayer(const std::string& name)
	{
		// Maximum number of players exceeded
		if (playerCount() >= gameData.settings.playerCount)
			return InvalidPlayerIndex;
		// If the role is occupied
		if (playerData.occupiedRoles[static_cast<std::underlying_type<Roles>::type>(R)])
			return InvalidPlayerIndex;
		playerData.occupiedRoles[static_cast<std::underlying_type<Roles>::type>(R)] = true;
		auto player = std::shared_ptr<PlayerBase>(new Player<R>(name));
		playerData.players.push_back(player);
		return static_cast<PlayerIndex>(playerData.players.size() - 1);;
	}

	const PlayerBase& Game::getPlayer(PlayerIndex i) const
	{
		return *playerData.players[i];
	}

	PlayerBase& Game::getPlayer(PlayerIndex i)
	{
		return *playerData.players[i];
	}

	bool Game::playerExists(PlayerIndex i) const
	{
		return (i < static_cast<PlayerIndex>(playerData.players.size()) && i >= 0);
	}
}
