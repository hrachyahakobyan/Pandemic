#include "stdafx.h"
#include "StateMachineTest.h"


namespace pan{
	TEST_F(StateMachineTest, Test1){
		using namespace pan;
		Game g(Settings::Beginner(2), Map::pandemicMap());
		auto p1 = g.addRandomPlayer("Potato");
		auto p2 = g.addRandomPlayer("Cabbage");

		ASSERT_TRUE(g.initialize());
		ASSERT_TRUE(g.stateMachine.gameData.initialized);

		auto& machine = g.stateMachine;
		ASSERT_EQ(machine.gameData.state, GameState::InProgress);
		ASSERT_EQ(machine.playerData.stage, PlayerStage::Act);

		ASSERT_FALSE(machine.playerCanAct(p2, ActionType::Move));
		ASSERT_FALSE(machine.playerCanAct(p2, ActionType::Draw));
		ASSERT_FALSE(machine.playerCanAct(p2, ActionType::Discard));
		ASSERT_FALSE(machine.playerCanAct(p2, ActionType::Infect));

		ASSERT_FALSE(machine.playerCanAct(p1, ActionType::Draw));
		ASSERT_FALSE(machine.playerCanAct(p1, ActionType::Discard));
		ASSERT_FALSE(machine.playerCanAct(p1, ActionType::Infect));

		ASSERT_TRUE(machine.playerCanAct(p1, ActionType::Move));

		machine.playerDidAct(p1, ActionType::Move);
		machine.playerDidAct(p1, ActionType::Move);
		machine.playerDidAct(p1, ActionType::Move);
		ASSERT_EQ(machine.playerData.stage, PlayerStage::Act);

		machine.playerDidAct(p1, ActionType::Move);
		ASSERT_EQ(machine.playerData.stage, PlayerStage::Draw);

		machine.playerDidAct(p1, ActionType::Draw);
		ASSERT_EQ(machine.playerData.stage, PlayerStage::Infect);

		machine.playerDidAct(p1, ActionType::Infect);
		ASSERT_EQ(machine.playerData.stage, PlayerStage::Act);
		ASSERT_EQ(machine.playerData.turn, p2);
	}
}