#pragma once
#include "GameStateMachine.h"
#include "ActionHandler.h"

namespace pan
{
	/**
	*	@brief Game entity which is responsible for
	*	connecting different pieces of the game logic together.
	*	@author Hrachya Hakobyan
	*/
	class Game 
	{
	public:
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
		*	attempt to initialize the game.
		*	The game will be initialized only once.
		*	The game will be initialized if all preconditions are met,
		*	e.g. the game has the required number of players and/or any other precondition.
		*	@return true if the game successfully initialzed, false otherwise
		*/
		bool initialize();

		/**
		*	get whether the game is initialized
		*	@return true if the game is initialized
		*/
		inline bool isInitialized() const;	

		/**
		*	whether the game is over.
		*	The game is over if the status is either Victory or Defeat
		*/
		inline bool isOver() const;

		/**
		*	get the current state of the game.
		*	The game can either be running, or over.
		*	A game that is over either has a state of Victory or Defeat
		*	@return the current state of the game
		*/
		inline GameState getState() const;

		/**
		*	get the current stage of a player
		*	@return the stage of the current player
		*/
		inline PlayerStage getStage() const;

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

		inline PlayerIndex getActivePlayerIndex() const;
		inline const PlayerBase& getActivePlayer() const;

		/**
		*	Adds a new action to the action queue
		*	If the game is not initialized or is over, the method will have no effect.
		*	@param action the action to be added.
		*/
		void addAction(const ActionBase& action);

		/**
		*	Executes actions in the action queue.
		*	If the game is not initialized or is over, the method will have no effect.
		*	If the action is invalid, it will be removed from the action queue.
		*	If there are no action, the method will have no effect.
		*/
		void execute();

		/**
		*	Executes all actions in the action queue.
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
		ActionHandler actionHandler;
		GameStateMachine stateMachine;
		ActionData actionData;
		friend class ActionHandler;
		friend class GameStateMachine;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar.template register_type<pan::GameStateMachine>();
			ar & BOOST_SERIALIZATION_NVP(stateMachine);
		}

		void initialInfections();

#ifdef _DEBUG
#ifndef DISABLE_TESTS
		FRIEND_TESTS
#endif
#endif
	};

	std::size_t Game::playerCount() const
	{
		return getPlayerData().players.size();
	}

	bool Game::operator!=(const Game& o) const
	{
		return !((*this) == o);
	}

	bool Game::isInitialized() const
	{
		return stateMachine.getGameData().initialized;
	}

	bool Game::isOver() const
	{
		return stateMachine.getGameData().state != GameState::InProgress;
	}

	GameState Game::getState() const
	{
		return stateMachine.getGameData().state;
	}

	const Map& Game::getMap() const
	{
		return stateMachine.getMap();;
	}

	const PlayerData& Game::getPlayerData() const
	{
		return stateMachine.getPlayerData();
	}

	const GameData& Game::getGameData() const
	{
		return stateMachine.getGameData();
	}

	const DeckData& Game::getDeckData() const
	{
		return stateMachine.getDeckData();
	}

	template<Roles R>
	PlayerIndex Game::addPlayer(const std::string& name)
	{
		return stateMachine.addPlayer<R>(name);
	}

	const PlayerBase& Game::getPlayer(PlayerIndex i) const
	{
		return *stateMachine.getPlayerData().players[i];
	}

	const PlayerBase& Game::getActivePlayer() const
	{
		return stateMachine.getPlayer(getActivePlayerIndex());
	}

	PlayerIndex Game::getActivePlayerIndex() const
	{
		return stateMachine.getPlayerData().turn;
	}
}
