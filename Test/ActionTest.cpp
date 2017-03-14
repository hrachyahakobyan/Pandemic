#include "stdafx.h"
#include "ActionTest.h"
#include "Game.h"
#include "Infect.h"
#include "Outbreak.h"

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
}
