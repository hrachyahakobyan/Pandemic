#include "stdafx.h"
#include "ActionHandler.h"
#include "Move.h"
#include "Game.h"

namespace pan{

	ActionHandler::ActionHandler(Game& game) :
		game(game)
	{

	}

	ActionHandler::~ActionHandler()
	{

	}

	template<>
	bool ActionHandler::validate<Move>(const Move& m) const{
		if (!game.map.cityExists(m.targetCity) ||
			!game.playerExists(m.initiater) ||
			!game.playerExists(m.targetPlayer)){
			return false;
		}
		return true;
	}

	template<>
	void ActionHandler::execute<Move>(const Move& m) const{
		if (!m.validate(*this)){
			return;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.targetPlayer);
		// Remove from previous city
		game.map[player.getLocation()].removePlayer(m.targetPlayer);
		// Add to the target city
		game.map[m.targetCity].addPlayer(m.targetPlayer);
		// Update the player's location
		player.setLocation(m.targetCity);
	}
}