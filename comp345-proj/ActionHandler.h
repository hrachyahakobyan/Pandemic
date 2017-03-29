#pragma once

namespace pan{
	class Game;
	class Outbreak;
	class Infect;
	/**
	*	@brief Class containing the logic of validating and executing actions.
	*	Directly connected to a Game object through a reference.
	*	Does not store any state, is free from serialization.
	*	@author Hrachya Hakobyan
	*/
	class ActionHandler
	{
	public:
		explicit ActionHandler(Game& game);
		ActionHandler() = delete;
		ActionHandler(const ActionHandler&) = delete;
		~ActionHandler();

		/**
		*	Validates the given action
		*	@param action a subclass of ActionImpl
		*	@return true if the action is valid, false otherwise
		*/
		template<typename Action>
		bool validate(const Action& action) const;

		/**
		*	Executes the given action.
		*	The action is validated before execution.
		*	A valid action will always execute.
		*	@param action a subclass of ActionImpl
		*	@return true if the action was valid, false otherwise
		*/
		template<typename Action>
		bool execute(const Action& action);
	private:
		Game& game;
#ifdef _DEBUG
#ifndef DISABLE_TESTS
		FRIEND_TESTS
#endif
#endif

		//bool isPlayersTurn(PlayerIndex i) const;
		/**
		*	Tells whether the given player can act, i.e. perform one of 4 actions.
		*	A player can perform an action if it is his/her turn, the current stage
		*	is Act and the player has not yet exhausted all his/her action
		*	@return true if it is the players turn
		*/
		//bool playerCanAct(PlayerIndex i) const;
		/**
		*	commits a player action.
		*	If its the turn of the player in question, the current stage is Act
		*	the action counter will be incremented. If by doing so the player exhausts
		*	his/her actions, the stage of the game will be changed to draw
		*	@return true if the player is allowed to act
		*/
		//void commitAction(PlayerIndex i);

		/**
		*	Actual implementation of outbreak
		*	@param out the Outbreak action object
		*	@param infected the set of all infected cities caused by the initial infection and its chain reactions if any
		*	@return true if the action was successfully executed
		*/
		bool outBreakImpl(const Outbreak& out, std::set<CityIndex>& infected);
		/**
		*	Actual implementation of an infection
		*	@param inf the Infect action object
		*	@param infected the set of all infected cities caused by the initial infection and its chain reactions if any
		*	@return true if the action was successfully executed
		*/
		bool infectImpl(const Infect& inf, std::set<CityIndex>& infected);

		/**
		*	Moves a player to the specified location
		*	@param player the player to be moved
		*	@target the target city
		*/
		//void moveImpl(PlayerIndex player, CityIndex target);
	};
}

