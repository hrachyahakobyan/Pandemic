#include "stdafx.h"
#include "GameTest.h"
#include "Role.h"
#include "Map.h"
#include "Game.h"
#include "common.h"
#include "misc.h"


namespace pan{
	GameTest::GameTest()
	{
	}


	GameTest::~GameTest()
	{
	}

	/**
	*	@brief tests the functionality of Game class to add players
	*	@author Hrachya Hakobyan
	*/
	TEST_F(GameTest, addsPlayers){
		using namespace pan;
		Game game;
		ASSERT_EQ(game.playerCount(), 0);
		auto p1 = game.addPlayer<Roles::Medic>("Hrachya");
		ASSERT_TRUE(game.playerExists(p1));
		ASSERT_EQ(game.getPlayer(p1).getLocation(), 0);
		ASSERT_EQ(game.playerCount(), 1);
		auto p2 = game.addPlayer<Roles::Dispatcher>("Terence");
		ASSERT_TRUE(game.playerExists(p2));
		ASSERT_EQ(game.getPlayer(p2).getLocation(), 0);
		ASSERT_EQ(game.playerCount(), 2);
	}

	/**
	*	@brief tests the functionality of Game class to serialize
	*	@author Hrachya Hakobyan
	*/
	TEST_F(GameTest, serializes){
		using namespace pan;

		Game game;
		auto c0 = game.map.addCity();
		game.map[c0].setName("Atlanta");
		auto c1 = game.map.addCity();
		game.map[c1].setName("Montreal");
		game.map.addConnection(c0, c1);
		game.map[c0].population = 233123;
		game.map[c1].population = 3310231;
		game.map[c0].researchStation = true;

		auto p1 = game.addPlayer<Roles::Medic>("Hrachya");
		auto p2 = game.addPlayer<Roles::Dispatcher>("Terence");

		game.map[c0].addPlayer(p1);
		game.map[c1].addPlayer(p2);

		std::string filename("temp/GameSerialization.xml");
		std::ofstream ofs(filename.c_str());
		ASSERT_TRUE(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		registerTypes(oa);
		ASSERT_NO_THROW(oa << boost::serialization::make_nvp("Game", game));
		ofs.close();

		Game newGame;
		std::ifstream ifs(filename.c_str());
		ASSERT_TRUE(ifs.good());
		boost::archive::xml_iarchive ia(ifs);
		registerTypes(ia);
		ASSERT_NO_THROW(ia >> boost::serialization::make_nvp("Game", newGame));
		ifs.close();
		ASSERT_TRUE(game == newGame);
	}

	TEST_F(GameTest, executes){
		using namespace pan;
		Game game(Settings::Beginner(2), Map::pandemicMap());
		auto validP = game.addPlayer<Roles::Medic>("Hrachya");
		auto validP2 = game.addPlayer<Roles::Dispatcher>("Liu");
		auto cityCount = game.map.numCities();
		auto validCity = cityCount - 1;
		auto validCity2 = cityCount - 2;
		EXPECT_TRUE(validCity != 0);
		EXPECT_TRUE(validCity2 != 0);

		ASSERT_TRUE(game.map.cityExists(validCity));
		ASSERT_TRUE(game.map.cityExists(validCity2));
		PlayerIndex invalidP = game.playerCount();
		PlayerIndex invalidP2 = game.playerCount() + 1;
		ASSERT_FALSE(game.playerExists(invalidP));
		ASSERT_FALSE(game.playerExists(invalidP2));
		auto invalidCity = cityCount;
		auto invalidCity2 = cityCount + 1;
		ASSERT_FALSE(game.map.cityExists(invalidCity));
		ASSERT_FALSE(game.map.cityExists(invalidCity2));

		Move m;
		// Check move by invalid initiater
		m.initiater = invalidP;
		m.targetCity = validCity;
		m.targetPlayer = validP;
		ASSERT_FALSE(game.validate(m));

		// Check move by invalid target city
		m.initiater = validP;
		m.targetCity = invalidCity;
		m.targetPlayer = validP;
		ASSERT_FALSE(game.validate(m));

		// Check move by invalid target player
		m.initiater = validP;
		m.targetCity = validCity;
		m.targetPlayer = invalidP;
		ASSERT_FALSE(game.validate(m));

		// Check move by same player different city
		m.targetPlayer = validP;
		auto locationBefore = game.getPlayer(validP).getLocation();
		m.targetCity = validCity;
		auto expectedLocation = m.targetCity;
		EXPECT_NE(expectedLocation, locationBefore);
		EXPECT_EQ(m.initiater, m.targetPlayer);
		ASSERT_TRUE(game.validate(m));
		game.execute(m);
		auto locationAfter = game.getPlayer(m.targetPlayer).getLocation();
		ASSERT_EQ(locationAfter, expectedLocation);

		// Check move by same city different player
		m.targetPlayer = validP2;
		locationBefore = game.getPlayer(validP2).getLocation();
		m.targetCity = locationBefore;
		expectedLocation = m.targetCity;
		EXPECT_NE(m.initiater, m.targetPlayer);
		EXPECT_EQ(expectedLocation, locationBefore);
		ASSERT_TRUE(game.validate(m));
		game.execute(m);
		locationAfter = game.getPlayer(m.targetPlayer).getLocation();
		ASSERT_EQ(locationAfter, expectedLocation);

		// Check move by different city different player
		m.targetCity = validCity2;
		locationBefore = game.getPlayer(validP2).getLocation();
		expectedLocation = m.targetCity;
		EXPECT_NE(expectedLocation, locationBefore);
		EXPECT_NE(m.initiater, m.targetPlayer);
		ASSERT_TRUE(game.validate(m));
		game.execute(m);
		locationAfter = game.getPlayer(m.targetPlayer).getLocation();
		ASSERT_EQ(expectedLocation, locationAfter);
	}
}
