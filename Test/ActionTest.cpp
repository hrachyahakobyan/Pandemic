#include "stdafx.h"
#include "ActionTest.h"

namespace pan{

	TEST_F(ActionTest, Infect){
		using namespace pan;
		// Do not initialize the game to test the infection actions directly

		Infect infect(0, 0, 0);
		ASSERT_FALSE(infect.execute(game.actionHandler));

		// Invalid infection action, more than 3 cubes
		infect.cubes = 4;
		ASSERT_FALSE(infect.execute(game.actionHandler));

		// Valid infection, 2 cubes
		// Check the city's region coincides with the disease type
		EXPECT_EQ(game.map.regionForCity(infect.city), infect.diseaseType);
		infect.cubes = 2;
		std::size_t cubesBefore = game.gameData.diseaseCubes[infect.diseaseType];
		ASSERT_TRUE(infect.execute(game.actionHandler));
		// Check post conditions
		// The outbreak should not have occured
		ASSERT_EQ(game.gameData.outbreakMarker, 0);
		// The cubes must have decreased by the amount of infected cubes
		ASSERT_EQ(game.gameData.diseaseCubes[infect.diseaseType] + infect.cubes, cubesBefore);
		// Check the cubes of the city
		ASSERT_EQ(game.map[infect.city].getCubes(infect.diseaseType), infect.cubes);

		// Valid infection, 3 cubes
		infect.cubes = 2;
		// Change the city
		infect.city = 1;
		EXPECT_EQ(game.map.regionForCity(infect.city), infect.diseaseType);
		cubesBefore = game.gameData.diseaseCubes[infect.diseaseType];
		ASSERT_TRUE(infect.execute(game.actionHandler));
		// Check post conditions
		ASSERT_EQ(game.gameData.outbreakMarker, 0);
		ASSERT_EQ(game.gameData.diseaseCubes[infect.diseaseType] + infect.cubes, cubesBefore);
		ASSERT_EQ(game.map[infect.city].getCubes(infect.diseaseType), infect.cubes);

		// Invalid infection, more than one cube for a city with different region than the disease
		infect.diseaseType = 1;
		infect.cubes = 2;
		infect.city = 0;
		EXPECT_NE(game.map.regionForCity(infect.city), infect.diseaseType);
		ASSERT_FALSE(infect.execute(game.actionHandler));

		// Valid infection
		infect.cubes = 1;
		cubesBefore = game.gameData.diseaseCubes[infect.diseaseType];
		ASSERT_TRUE(infect.execute(game.actionHandler));
		// Check post conditions
		ASSERT_EQ(game.gameData.outbreakMarker, 0);
		ASSERT_EQ(game.gameData.diseaseCubes[infect.diseaseType] + infect.cubes, cubesBefore);
		ASSERT_EQ(game.map[infect.city].getCubes(infect.diseaseType), infect.cubes);

	}

	TEST_F(ActionTest, Outbreak){
		using namespace pan;
		// Do not initialize the game to test the infection actions directly

		Infect infect(0, 0, 0);
		Outbreak out(infect);
		// The outbreak will not take place since the city does not have 3 cubes of the
		// infection disease type
		ASSERT_FALSE(out.execute(game.actionHandler));

		// Infect the city with a disease of a different type
		// Cannot infect with more than one cube at once
		infect.cubes = 1;
		infect.diseaseType = 1;
		for (int i = 0; i < 3; i++){
			EXPECT_TRUE(infect.execute(game.actionHandler));
		}

		// The outbreak will still not occur
		ASSERT_FALSE(out.execute(game.actionHandler));

		infect.diseaseType = 0;
		infect.cubes = 3;
		EXPECT_TRUE(infect.execute(game.actionHandler));
		// Valid outbreak
		out = Outbreak(infect);
		ASSERT_TRUE(out.execute(game.actionHandler));
		// Check post conditions
		ASSERT_EQ(game.gameData.outbreakMarker, 1);
		// the number of cubes of the source city should not have changed
		ASSERT_EQ(game.map[out.infection.city].getCubes(out.infection.diseaseType), 3);
		// Check all neighbors of the source city
		Map::ConnectedCityIterator ai, ai_end;
		for (boost::tie(ai, ai_end) = game.map.connectedCities(out.infection.city);
			ai != ai_end; ++ai){
			// Check condition of each city
			ASSERT_EQ(game.map[*ai].getCubes(out.infection.diseaseType), 1);
		}
	}

	TEST_F(ActionTest, Move){
		using namespace pan;
		Game g(Settings::Beginner(2), Map::pandemicMap());
		auto p1Index = g.addPlayer<Roles::Medic>("Player1");
		auto p2Index = g.addPlayer<Roles::Dispatcher>("Player2");
		EXPECT_TRUE(g.initialize());
		const PlayerBase& p = static_cast<const Game&>(g).getPlayer(p1Index);
		// Invalid move. Moving to the same location
		Move m(0, p.getLocation());
		ASSERT_FALSE(m.execute(g.actionHandler));

		// Invalid move. Moving to a non neighbor city
		CityIndex city = g.map.numCities() - 1;
		EXPECT_FALSE(g.map.connectionExists(city, p.getLocation()));
		m.targetCity = city;
		ASSERT_FALSE(m.execute(g.actionHandler));

		// Valid move. Moving to a neigbor city
		city = static_cast<CityIndex>(1);
		EXPECT_TRUE(g.map.connectionExists(city, p.getLocation()));

		m.targetCity = city;
		ASSERT_TRUE(m.execute(g.actionHandler));
		// Check post conditions
		ASSERT_EQ(p.getLocation(), m.targetCity);
		ASSERT_TRUE(g.map[m.targetCity].containsPlayer(p1Index));
	}

	TEST_F(ActionTest, BuildResearchStation){
		using namespace pan;
		Game g(Settings::Beginner(2), Map::pandemicMap());
		auto p1Index = g.addPlayer<Roles::Medic>("Player1");
		auto p2Index = g.addPlayer<Roles::Dispatcher>("Player2");
		EXPECT_TRUE(g.initialize());
		PlayerBase& p = g.getPlayer(p1Index);
		// Give player some cards
		p.getCards().push(std::shared_ptr<CardBase>(new CityCard(0)));

		BuildResearchStation b(p1Index);
		// Cannot build a research station since it is already there
		ASSERT_FALSE(b.execute(g.actionHandler));

		// Move to a city with no research station
		Move m(p1Index, 1);
		EXPECT_TRUE(m.execute(g.actionHandler));
		// Cannot build because does not have a matching card
		ASSERT_FALSE(b.execute(g.actionHandler));

		// Add the required card
		p.getCards().push(std::shared_ptr<CardBase>(new CityCard(1)));
		g.gameData.researchStations = g.gameData.settings.maxResearchStations;
		// Cannot build since no more research stations can be built
		ASSERT_FALSE(b.execute(g.actionHandler));

		g.gameData.researchStations = 1;
		// Save the number of discarded player cards before execution
		std::size_t discardSizeBfore = g.deckData.playerDiscardDeck.size();
		std::size_t playerCardSizeBefore = p.getCards().size();
		// Must build
		ASSERT_TRUE(b.execute(g.actionHandler));
		// check post conditions
		ASSERT_TRUE(g.map[p.getLocation()].researchStation);
		ASSERT_EQ(g.gameData.researchStations, 2);
		ASSERT_EQ(p.getCards().size(), playerCardSizeBefore - 1);
		ASSERT_EQ(g.deckData.playerDiscardDeck.size(), discardSizeBfore + 1);
	}
}
