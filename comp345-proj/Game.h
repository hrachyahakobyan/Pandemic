#pragma once
#include "Map.h"
#include "Player.h"
#include "Move.h"
#include "ActionHandler.h"

namespace pan
{
	/**
	*	@brief Initial mock-up of the Game object which is responsible for
	*	connecting different pieces of the game logic together.
	*	@author Hrachya Hakobyan
	*/
	class Game : public Object
	{
	public:
		Game();
		explicit Game(const Map& m);
		Game(const Game&);
		Game(Game&&);
		Game& operator=(const Game&);
		Game& operator=(Game&& o);
		~Game();

		bool operator==(const Game&) const;
		inline bool operator!=(const Game&) const;

		/**
		*	Validates a given action
		*	@param action the action to validate
		*	@return true if the action is valid, false otherwise
		*/
		inline bool validate(const ActionBase& action) const;

		/**
		*	Executes a given action
		*	@param action the action to validate
		*/
		inline void execute(const ActionBase& action);
		inline const Map& getMap() const;

		std::string description() const;

		/**
		*	Adds a new player 
		*	@param name the name of the new player
		*	@return a unique index for the newly created players
		*/
		template<Roles R>
		PlayerIndex addPlayer(const std::string& name = "");

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

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object);
			ar & BOOST_SERIALIZATION_NVP(map);
			ar & BOOST_SERIALIZATION_NVP(players);
		}
	private:
		Map map;
		ActionHandler actionHandler;
		std::vector<std::shared_ptr<PlayerBase>> players;
		/**
		*	ActionHandler is a part of the logic of the game.
		*	Friend-ing increases encapsulation by avoiding making
		*	the private interface of the game public.
		*/
		friend class ActionHandler;
#ifdef _DEBUG
		friend class GameTest;
		FRIEND_TEST(GameTest, addsPlayers);
		FRIEND_TEST(GameTest, serializes);
		FRIEND_TEST(GameTest, validates);
		FRIEND_TEST(GameTest, executes);
#endif

		inline PlayerBase& getPlayer(PlayerIndex i);
	};

	std::size_t Game::playerCount() const
	{
		return players.size();
	}

	bool Game::operator!=(const Game& o) const
	{
		return !((*this) == o);
	}

	const Map& Game::getMap() const
	{
		return map;
	}

	bool Game::validate(const ActionBase& action) const
	{
		return action.validate(actionHandler);
	}

	void Game::execute(const ActionBase& action)
	{
		action.execute(actionHandler);
	}

	template<Roles R>
	PlayerIndex Game::addPlayer(const std::string& name)
	{
		auto player = std::shared_ptr<PlayerBase>(new Player<R>(name));
		player->setLocation(0);
		players.push_back(player);
		PlayerIndex index = static_cast<PlayerIndex>(players.size() - 1);
		Move move;
		move.initiater = index;
		move.targetCity = 0;
		move.targetPlayer = index;
		this->execute(move);
		return index;
	}

	const PlayerBase& Game::getPlayer(PlayerIndex i) const
	{
		return *players[i];
	}

	PlayerBase& Game::getPlayer(PlayerIndex i)
	{
		return *players[i];
	}

	bool Game::playerExists(PlayerIndex i) const
	{
		return (i < players.size());
	}
}



