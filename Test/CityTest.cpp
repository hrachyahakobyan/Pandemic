#include "stdafx.h"
#include "CityTest.h"
#include <core\FileManager.h>

namespace pan{
	TEST_F(CityTest, Serializes){
		using namespace pan;
		City c;
		c.setName("Atlanta");
		c.researchStation = true;
		c.population = 123123;
		c.setCubes(3, 3);
		c.setCubes(0, 3);
		c.setCubes(1, 2);
		c.addPlayer(PlayerPtr(new Dispatcher(0, "Potato")));

		ASSERT_TRUE(FileManager::getInstance().save(c, "CitySerialization.xml", "temp"));

		City cNew;
		ASSERT_TRUE(FileManager::getInstance().load(cNew, "CitySerialization.xml", "temp"));
		ASSERT_EQ(c, cNew);
	}
}