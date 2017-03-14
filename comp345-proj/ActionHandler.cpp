#include "stdafx.h"
#include "ActionHandler.h"
#include "Move.h"
#include "Game.h"
#include "Infect.h"
#include "Outbreak.h"

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
	bool ActionHandler::execute<Move>(const Move& m) const{
		if (!m.validate(*this)){
			return false;
		}
		// Get the player
		PlayerBase& player = game.getPlayer(m.targetPlayer);
		// Remove from previous city
		game.map[player.getLocation()].removePlayer(m.targetPlayer);
		// Add to the target city
		game.map[m.targetCity].addPlayer(m.targetPlayer);
		// Update the player's location
		player.setLocation(m.targetCity);
		return true;
	}

	template<>
	bool ActionHandler::validate<Outbreak>(const Outbreak& a) const{
		const auto& city = game.map[a.infection.city];
		// If the city does not have 3 cubes of the specified type,
		// the outbreak will not take place
		if (city.getCubes(a.infection.diseaseType) != 3){
			return false;
		} 
		return true;
	}

	template<>
	bool ActionHandler::execute<Outbreak>(const Outbreak& a) const{
		// The current city has already suffered an outbreak due to the same infection
		if (a.infection.outbreakedCities.find(a.infection.city) != a.infection.outbreakedCities.end()){
			return true;
		}
		// Check the outbreak marker
		// If it is on max, the game is lost
		if (game.gameData.outbreakMarker == game.gameData.settings.outbreakMarkerMax){
			game.changeStatus(Game::Status::Defeat);
			return true;
		}
		// Otherwise, infect each neighbor
		Map::ConnectedCityIterator ai, ai_end;
		bool result = true;
		for (boost::tie(ai, ai_end) = game.map.connectedCities(a.infection.city);
			ai != ai_end; ++ai){
			// Create a new infection whose target is the neighbor
			Infect infect(*ai, a.infection.diseaseType, 1);
			infect.outbreakedCities = a.infection.outbreakedCities;
			// Add the currently outbreaked city to the set of outbreaked cities
			// of the new infection
			infect.outbreakedCities.insert(a.infection.city);
			result = result && infect.execute(*this);
		}
		return result;
	}

	template<>
	bool ActionHandler::validate<Infect>(const Infect& a) const{
		return true;
	}

	template<>
	bool ActionHandler::execute<Infect>(const Infect& a) const{
		if (!a.validate(*this)){
			return false;
		}
		// Get the city reference
		auto& city = game.map[a.city];
		// The current cubes of the city of the givem diseaseType
		std::size_t currentCubes = city.getCubes(a.diseaseType);
		// How many more the city is able to take
		std::size_t canTake = 3 - currentCubes;
		// How many cubes are left in the game
		std::size_t cubesLeft = game.gameData.diseaseCubes[a.diseaseType];
		// How many the city will actually take
		// The minimum of how many it can actually take, and how many it is required to take
		std::size_t willTake = std::min(canTake, a.cubes);
		// If there are less cubes left than the city will actually take
		// automatically the game is lost.
		if (willTake > cubesLeft){
			game.changeStatus(Game::Status::Defeat);
			return true;
		}
		// Otherwise, increase the number of cubes in the city
		city.setCubes(a.diseaseType, currentCubes + willTake);
		// And decrease from cubes left
		game.gameData.diseaseCubes[a.diseaseType] = cubesLeft - willTake;

		// Outbreak if there city took less cubes than it should have
		if (willTake < a.cubes){
			Outbreak out(a);
			return out.execute(*this);
		}
		return true;
	}
}