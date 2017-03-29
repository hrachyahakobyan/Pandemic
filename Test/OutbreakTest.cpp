#include "stdafx.h"
#include "OutbreakTest.h"

namespace pan{
	TEST_F(OutbreakTest, Test1)
	{
		using namespace pan;
		Map m;
		auto c1 = m.addCity();
		auto c2 = m.addCity();
		m.addConnection(c1, c2);
		Settings s = Settings::Beginner(2);
		s.initialCards = 0;
		Game game(s, m);
		auto p1 = game.addPlayer<Roles::Medic>("P1");
		auto p2 = game.addPlayer<Roles::Dispatcher>("P2");
		game.stateMachine.initDiseases();
		game.stateMachine.initCards();
		game.stateMachine.initPlayers();

		Infect inf(0, 0, 2);
		ASSERT_TRUE(inf.execute(game.actionHandler));
		// No outbreak
		ASSERT_EQ(game.stateMachine.getGameData().outbreakMarker, 0);
		ASSERT_EQ(game.stateMachine.getMap()[inf.city].getCubes(inf.diseaseType), inf.cubes);

		inf.city = 1;
		ASSERT_TRUE(inf.execute(game.actionHandler));
		// No outbreak
		ASSERT_EQ(game.stateMachine.getGameData().outbreakMarker, 0);
		ASSERT_EQ(game.stateMachine.getMap()[inf.city].getCubes(inf.diseaseType), inf.cubes);	

		// Will cause outbreak and chain reaction
		// however must not re-outbreak the initial city
		ASSERT_TRUE(inf.execute(game.actionHandler));
		ASSERT_EQ(game.stateMachine.getGameData().outbreakMarker, 1);
		ASSERT_EQ(game.stateMachine.getGameData().diseaseCubes[inf.diseaseType], s.diseaseCubesPerDisease - 6);
		ASSERT_EQ(game.stateMachine.getMap()[0].getCubes(inf.diseaseType), 3);
		ASSERT_EQ(game.stateMachine.getMap()[1].getCubes(inf.diseaseType), 3);

		// Further outbreaks cause an increase of marker by two but do not decrease the number
		// of disease cubes
		auto cubesCount = game.stateMachine.getGameData().diseaseCubes[inf.diseaseType];
		ASSERT_TRUE(inf.execute(game.actionHandler));
		ASSERT_EQ(game.stateMachine.getGameData().outbreakMarker, 3);
		ASSERT_EQ(game.stateMachine.getGameData().diseaseCubes[inf.diseaseType], cubesCount);
	}

	TEST_F(OutbreakTest, Test2)
	{
		using namespace pan;
		Map m;
		const std::size_t n = 5;
		auto cPrev = m.addCity();
		auto cInitial = cPrev;
		auto cNext = cPrev;
		for (std::size_t i = 1; i < n; i++){
			cNext = m.addCity();
			m.addConnection(cNext, cPrev);
			cPrev = cNext;
		}
		m.addConnection(cInitial, cNext);

		Settings s = Settings::Beginner(2);
		s.initialCards = 0;
		Game game(s, m);
		auto p1 = game.addPlayer<Roles::Medic>("P1");
		auto p2 = game.addPlayer<Roles::Dispatcher>("P2");
		game.stateMachine.initDiseases();
		game.stateMachine.initCards();
		game.stateMachine.initPlayers();

		// Infect all cities with 3 cubes
		Infect inf(cInitial, 0, 3);
		for (std::size_t i = 0; i < n; i++){
			inf.city = i;
			ASSERT_TRUE(inf.execute(game.actionHandler));
			ASSERT_EQ(game.stateMachine.getGameData().outbreakMarker, 0);
			ASSERT_EQ(game.stateMachine.getMap()[i].getCubes(inf.diseaseType), inf.cubes);
		}

		// Will cause a chain outbreak, all n cities will suffer and outbreak
		auto cubesSize = game.stateMachine.getGameData().diseaseCubes[inf.diseaseType];
		ASSERT_TRUE(inf.execute(game.actionHandler));
		ASSERT_EQ(game.stateMachine.getGameData().outbreakMarker, n);
		// The diseases cubes will decrease by n
		ASSERT_EQ(game.stateMachine.getGameData().diseaseCubes[inf.diseaseType], cubesSize);
	}
}