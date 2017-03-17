#pragma once

namespace pan{
	class GameplayTest : public ::testing::Test
	{
	protected:
		pan::CityIndex getNeighbor(CityIndex i, const pan::Map& m) const;
	};
}

