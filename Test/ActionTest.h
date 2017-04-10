#pragma once

namespace pan{
	class ActionTest : public ::testing::Test
	{
	protected:
		Game game;
		virtual void SetUp(){
			game = Game(Settings::Beginner(2), Map::pandemicMap());
			// Add the diseases based on.stateMachine.getMap() regions
			for (auto diseaseType : game.stateMachine.getMap().getRegions()){
				game.stateMachine.gameData.diseases.push_back(Disease(diseaseType));
			}

			// Construct the disease cubes
			for (std::size_t i = 0; i < game.stateMachine.getGameData().diseases.size(); i++){
				game.stateMachine.gameData.diseaseCubes.push_back(game.stateMachine.getGameData().settings.diseaseCubesPerDisease);
			}
		}

		pan::CityIndex getNeighbor(CityIndex i, const pan::Map& m) const;
	};
}

