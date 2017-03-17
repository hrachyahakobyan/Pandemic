#pragma once

namespace pan{
	class ActionTest : public ::testing::Test
	{
	protected:
		Game game;
		virtual void SetUp(){
			game = Game(Settings::Beginner(2), Map::pandemicMap());
			// Add the diseases based on map regions
			for (auto diseaseType : game.map.getRegions()){
				game.gameData.diseases.push_back(Disease(diseaseType));
			}

			// Construct the disease cubes
			for (std::size_t i = 0; i < game.gameData.diseases.size(); i++){
				game.gameData.diseaseCubes.push_back(game.gameData.settings.diseaseCubesPerDisease);
			}
		}

		pan::CityIndex getNeighbor(CityIndex i, const pan::Map& m) const;
	};
}

