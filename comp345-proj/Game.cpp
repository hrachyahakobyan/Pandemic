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
		stateMachine(s)
	{
	}

	Game::Game(const Settings& s, const Map& m) :
		actionHandler(*this),
		stateMachine(s, m)
	{
	}

	Game::Game(const Game& o) :
		actionHandler(*this),
		stateMachine(o.stateMachine)
	{
	}

	Game::Game(Game&& o) :
		actionHandler(*this),
		stateMachine(std::move(o.stateMachine))
	{
	}

	Game::~Game()
	{
	}

	Game& Game::operator=(const Game& o)
	{
		this->stateMachine = o.stateMachine;
		return *this;
	}

	Game& Game::operator=(Game&& o)
	{
		this->stateMachine = std::move(o.stateMachine);
		return *this;
	}

	bool Game::operator==(const Game& o) const
	{
		return (this->stateMachine == o.stateMachine);
	}

	bool Game::initialize()
	{
		bool init = stateMachine.getGameData().initialized;
		if (!init){
			if (stateMachine.initialize()){
				initialInfections();
			}
		}
		return stateMachine.getGameData().initialized;
	}

	void Game::initialInfections()
	{
		for (std::size_t cubes = 3; cubes > 0; cubes--){
			for (std::size_t card = 0; card < 3; card++){
				// Get top card
				auto cardPtr = stateMachine.drawInfectionDeckTop();
				// The disease type
				int size = stateMachine.getMap().numCities();
				DiseaseType type = stateMachine.getMap()[cardPtr->cityIndex].getRegion();
				// Infect
				Infect infect(cardPtr->cityIndex, type, cubes);
				infect.execute(actionHandler);
			}
		}
	}

	std::string Game::description() const
	{
		return stateMachine.description();
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
		if (action->execute(actionHandler)){
			actionData.completedActions.push(action);
			detail::NotificationCenter::defaultCenter().postNotification(std::shared_ptr<detail::Notification>(new ActionNotification(*action)));
		}
	}

	void Game::executeAll()
	{
		if (!isInitialized() || isOver())
			return;
		while (actionData.actionQueue.empty())
			execute();
	}

	bool Game::save(const std::string& name) const
	{
		return FileManager::getInstance().save(*this, name, "save");
	}

	bool Game::load(const std::string& name, Game& game)
	{
		return FileManager::getInstance().load(game, name, "save");
	}

	PlayerIndex Game::addRandomPlayer(const std::string& name)
	{
		return stateMachine.addRandomPlayer(name);
	}
}