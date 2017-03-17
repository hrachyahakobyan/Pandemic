#include "stdafx.h"
#include "GameTest.h"
#include <core/FileManager.h>

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
		std::size_t maxPlayers = 4;
		Settings s = Settings::Beginner(2);
		Game game(s);

		ASSERT_EQ(game.playerCount(), 0);
		auto p1 = game.addPlayer<Roles::Medic>("Hrachya");
		ASSERT_NE(p1, Game::InvalidPlayerIndex);
		ASSERT_TRUE(game.playerExists(p1));
		ASSERT_EQ(game.playerCount(), 1);

		// Attempt to add the same role
		auto invalidP = game.addPlayer<Roles::Medic>("Hrachya");
		ASSERT_EQ(invalidP, Game::InvalidPlayerIndex);
		ASSERT_FALSE(game.playerExists(invalidP));
		ASSERT_EQ(game.playerCount(), 1);

		auto p2 = game.addPlayer<Roles::Dispatcher>("Terence");
		ASSERT_TRUE(game.playerExists(p2));
		ASSERT_EQ(game.getPlayer(p2).getLocation(), 0);
		ASSERT_EQ(game.playerCount(), 2);

		// attempt to add 3rd player
		invalidP = game.addPlayer<Roles::FOperative>("Invalid");
		ASSERT_EQ(invalidP, Game::InvalidPlayerIndex);
		ASSERT_EQ(game.playerCount(), 2);
	}

	/**
	*	@brief tests the functionality of Game class to initialize
	*	@author Hrachya Hakobyan
	*/
	TEST_F(GameTest, initializes){
		Settings s = Settings::Beginner(2);
		// Use the actual map
		Game g(s, Map::pandemicMap());

		ASSERT_FALSE(g.isInitialized());
		ASSERT_FALSE(g.isOver());
		
		ASSERT_FALSE(g.initialize());

		// add a player
		g.addPlayer<Roles::Medic>("Player");
		ASSERT_EQ(g.playerCount(), 1);

		ASSERT_FALSE(g.initialize());

		g.addPlayer<Roles::Dispatcher>("Player");
		ASSERT_EQ(g.playerCount(), 2);

		ASSERT_TRUE(g.initialize());

		// Check initialization post conditions
		// Check players' deck sizes
		for (const auto& p : g.playerData.players){
			ASSERT_EQ(p->getCards().size(), s.initialCards);
		}

		// Check the player deck size
		// The size equals the total number of cities + total number of events + epidemic card count - the cards dealt to players
		std::size_t playerDeckSize = g.map.numCities() + EventTypeDescriptions.size() + g.gameData.settings.epidemicCardCount - g.playerCount() * g.gameData.settings.initialCards;
		ASSERT_EQ(g.deckData.playerDeck.size(), playerDeckSize);
		ASSERT_TRUE(g.deckData.playerDiscardDeck.empty());

		// The size of the infection card = total number of cities - 9 cards drawn at initialization
		ASSERT_EQ(g.deckData.infectionDeck.size(), g.map.numCities() - 9);
		// 9 drawn cards are in the discard pile
		ASSERT_EQ(g.deckData.infectionDiscardDeck.size(), 9);

		ASSERT_TRUE(g.actionData.completedActions.empty());
		ASSERT_TRUE(g.actionData.actionQueue.empty());
		// The initialization infection step cannot cause outbreaks
		ASSERT_EQ(g.gameData.outbreakMarker, 0);
		ASSERT_EQ(g.gameData.researchStations, 1);
	}

	/**
	*	@brief tests the functionality of Game class to serialize
	*	@author Hrachya Hakobyan
	*/
	TEST_F(GameTest, serializes){
		using namespace pan;
		Settings s = Settings::Beginner(2);
		Game game(s, Map::pandemicMap());
		game.addPlayer<Roles::Medic>("Player");
		game.addPlayer<Roles::Dispatcher>("Player");
		EXPECT_TRUE(game.initialize());
		ASSERT_TRUE(FileManager::getInstance().save(game, "GameSerialization.xml", "temp", true));
		Game newGame;
		ASSERT_TRUE(FileManager::getInstance().load(newGame, "GameSerialization.xml", "temp"));
		ASSERT_TRUE(game == newGame);
	}

	TEST_F(GameTest, executes){
		using namespace pan;
		/*
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
		*/
	}
}
