#include "stdafx.h"
#include "GameplayTest.h"
#include <core/Core.hpp>

namespace pan{
	TEST_F(GameplayTest, Test1){
		Game game(Settings::Beginner(2), Map::pandemicMap());

		auto p1 = game.addRandomPlayer("Player 1");
		auto p2 = game.addRandomPlayer("Player 2");

		ASSERT_NE(p1, GameStateMachine::InvalidPlayerIndex);
		ASSERT_NE(p2, GameStateMachine::InvalidPlayerIndex);

		ASSERT_TRUE(game.initialize());


		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
		// Player 1's turn
		// move
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 0);
		auto p1Loc = game.getPlayer(p1).getLocation();
		auto p1Neighbor = getNeighbor(p1Loc, game.stateMachine.getMap());
		Move m(p1, p1Neighbor);
		game.addAction(m);
		game.execute();
		ASSERT_EQ(game.getPlayer(p1).getLocation(), m.targetCity);
		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 1);
		EXPECT_FALSE(game.stateMachine.getMap()[m.targetCity].researchStation);

		// Build a research station
		// Add a card so he can build a station
		game.stateMachine.getPlayer(p1).getCards().pop();
		auto cityIndex = game.getPlayer(p1).getLocation();
		auto regionIndex = game.stateMachine.getMap()[cityIndex].getRegion();
		game.stateMachine.getPlayer(p1).getCards().push(std::shared_ptr<CardBase>(new CityCard(cityIndex, regionIndex)));

		std::size_t cardsBefore = game.getPlayer(p1).getCards().size();
		BuildResearchStation b(p1);
		game.addAction(b);
		game.execute();
		ASSERT_EQ(game.stateMachine.getGameData().researchStations, 2);
		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 2);
		ASSERT_TRUE(game.stateMachine.getMap()[m.targetCity].researchStation);
		ASSERT_EQ(game.getPlayer(p1).getCards().size(), cardsBefore - 1);

		// Add a city card matching the location and move somewhere else
		// Charter flight
		game.stateMachine.getPlayer(p1).getCards().pop();
		cityIndex = game.getPlayer(p1).getLocation();
		regionIndex = game.stateMachine.getMap()[cityIndex].getRegion();
		game.stateMachine.getPlayer(p1).getCards().push(std::shared_ptr<CardBase>(new CityCard(cityIndex, regionIndex)));
		cardsBefore = game.getPlayer(p1).getCards().size();
		CityIndex destC = game.stateMachine.getMap().numCities() - 1;
		CharterFlight ch(p1, destC);
		game.addAction(ch);
		game.execute();
		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 3);
		ASSERT_EQ(game.getPlayer(p1).getLocation(), ch.targetCity);
		ASSERT_EQ(game.getPlayer(p1).getCards().size(), cardsBefore - 1);

		// Add a new card
		// Let the player make a direct flight to the initial city
		game.stateMachine.getPlayer(p1).getCards().pop();
		game.stateMachine.getPlayer(p1).getCards().push(std::shared_ptr<CardBase>(new CityCard(0, 0)));
		cardsBefore = game.getPlayer(p1).getCards().size();

		DirectFlight df(p1, 0);
		game.addAction(df);
		game.execute();
		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 0);
		ASSERT_EQ(game.getPlayer(p1).getLocation(), df.targetCity);
		ASSERT_EQ(game.getPlayer(p1).getCards().size(), cardsBefore - 1);

		// Act step is done
		// Draw step
		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
		ASSERT_EQ(game.stateMachine.getPlayerData().stage, PlayerStage::Draw);
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 0);

		cardsBefore = game.getPlayer(p1).getCards().size();
		DrawPlayerCards dc(p1);
		game.addAction(dc);
		game.execute();

		// Check the number of new cards
		std::size_t cardsAfter = game.getPlayer(p1).getCards().size();
	
		if (cardsAfter != cardsBefore + game.stateMachine.getGameData().settings.playerDrawCount){
			// Epidemic took place
			ASSERT_NE(game.stateMachine.getGameData().infectionRateMarker, 0);
		}

		if (cardsAfter > game.stateMachine.getGameData().settings.playerHandMax){
			ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
			ASSERT_EQ(game.stateMachine.getPlayerData().stage, PlayerStage::Discard);
			ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 0);

			// Handle discard state...
		}

		// Infect step
		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p1);
		ASSERT_EQ(game.stateMachine.getPlayerData().stage, PlayerStage::Infect);
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 0);

		PlayerInfect pInf(p1);
		game.addAction(pInf);
		game.execute();

		// Player 1 is done
		ASSERT_EQ(game.stateMachine.getPlayerData().turn, p2);
		ASSERT_EQ(game.stateMachine.getPlayerData().stage, PlayerStage::Act);
		ASSERT_EQ(game.stateMachine.getPlayerData().actionCounter, 0);

	}


	pan::CityIndex GameplayTest::getNeighbor(CityIndex i, const pan::Map& m) const
	{
		Map::ConnectedCityIterator ai, ai_end;
		for (boost::tie(ai, ai_end) = m.connectedCities(i); ai != ai_end; ++ai){
			return *ai;
		}
		// return invalid index 
		return m.numCities() + 1;
	}
}