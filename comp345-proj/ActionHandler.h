#pragma once

namespace pan{
	class Game;
	/**
	*	@brief Class containing the logic of validating and executing actions.
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
		*	@param actionn a subclass of ActionImpl
		*	@return true if the action is valid, false otherwise
		*/
		template<typename Action>
		bool validate(const Action& action) const;

		/**
		*	Executes the given action
		*	@param actionn a subclass of ActionImpl
		*	@return true if the action was valid, false otherwise
		*/
		template<typename Action>
		bool execute(const Action& action) const;
	private:
		Game& game;
#ifdef _DEBUG
		FRIEND_TEST(ActionTest, Infect);
		FRIEND_TEST(ActionTest, Outbreak);
		FRIEND_TEST(ActionTest, Move);
		FRIEND_TEST(ActionTest, CharterFlight);
		FRIEND_TEST(ActionTest, ShuttleFlight);
		FRIEND_TEST(ActionTest, DirectFlight);
		FRIEND_TEST(ActionTest, BuildResearchStation);
#endif
	};
}

