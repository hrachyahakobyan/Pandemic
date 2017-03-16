#include "stdafx.h"
#include "MapTest.h"

namespace pan{
	/**
	*	@brief tests the functionality of Map class to add/remove cities
	*	@author Hrachya Hakobyan
	*/
	TEST_F(MapTest, addsRemovesCity){
		using namespace pan;
		pan::Map map;
		ASSERT_EQ(map.numCities(), 0);
		// Remove nonexistent city
		map.removeCity(0);
		// Check addition
		auto c1 = map.addCity();
		ASSERT_EQ(map.numCities(), 1);
		// Check removeal
		map.removeCity(c1);
		ASSERT_EQ(map.numCities(), 0);
		// Check double removal
		map.removeCity(c1);
		ASSERT_EQ(map.numCities(), 0);
	}

	/**
	*	@brief tests the functionality of Map class to add/remove connections
	*	@author Hrachya Hakobyan
	*/
	TEST_F(MapTest, addsRemovesConnections){
		using namespace pan;
		pan::Map map;
		// Remove nonexistent connection
		map.removeConnection(0, 0);
		map.removeConnection(1, 0);
		ASSERT_EQ(map.numConnections(), 0);
		auto c1 = map.addCity();
		ASSERT_FALSE(map.addConnection(c1, 1).second);
		ASSERT_FALSE(map.addConnection(1, c1).second);
		ASSERT_EQ(map.numConnections(), 0);
		ASSERT_FALSE(map.connectionExists(2, 2));
		ASSERT_FALSE(map.connectionExists(c1, c1));
		ASSERT_TRUE(map.addConnection(c1, c1).second);
		ASSERT_FALSE(map.addConnection(c1, c1).second);
		ASSERT_TRUE(map.connectionExists(c1, c1));
		ASSERT_EQ(map.numConnections(), 1);
		map.removeConnection(c1, c1);
		ASSERT_EQ(map.numConnections(), 0);
		ASSERT_FALSE(map.connectionExists(c1, c1));
		ASSERT_TRUE(map.addConnection(c1, c1).second);
		ASSERT_EQ(map.numConnections(), 1);
		auto c2 = map.addCity();
		ASSERT_FALSE(map.connectionExists(c1, c2));
		ASSERT_TRUE(map.addConnection(c1, c2).second);
		ASSERT_FALSE(map.addConnection(c2, c1).second);
		ASSERT_TRUE(map.connectionExists(c1, c2));
		ASSERT_TRUE(map.connectionExists(c2, c1));
		ASSERT_EQ(map.numConnections(), 2);
	}

	/**
	*	@brief tests the functionality of Map class to add/remove regions
	*	@author Hrachya Hakobyan
	*/
	TEST_F(MapTest, addsRemovesRegions){
		using namespace pan;
		pan::Map map;
		const int vCount = 10;
		// Add dummy data
		for (int i = 0; i < vCount; i++){
			map.addCity();
		}
		ASSERT_EQ(map.numCities(), vCount);
		// Remove nonexistent region
		ASSERT_FALSE(map.removeRegion(1));
		// Check initial region count
		ASSERT_EQ(map.numRegions(), 1);
		// Attempt to delete the only region
		const RoleIndex region0 = 0;
		ASSERT_THROW(map.removeRegion(region0), std::exception);
		// Add a region
		auto region1 = map.addRegion();
		ASSERT_EQ(map.numRegions(), 2);
		// Remove region 0
		ASSERT_TRUE(map.removeRegion(region0));
		// Remove twice
		ASSERT_FALSE(map.removeRegion(region0));
		ASSERT_EQ(map.numRegions(), 1);
		ASSERT_THROW(map.removeRegion(region1), std::exception);	
	}

	/**
	*	@brief tests the functionality of Map class to assign vertices to regions
	*	@author Hrachya Hakobyan
	*/
	TEST_F(MapTest, assignsRegions){
		using namespace pan;
		pan::Map map;
		const int vCount = 10;
		// Add dummy data
		const RoleIndex r0 = 0;
		for (int i = 0; i < vCount; i++){
			auto c = map.addCity();
			ASSERT_EQ(map.regionForCity(c), r0);
		}
		ASSERT_EQ(map.regionCities(r0).size(), vCount);
		// Add city to nonexistent region
		ASSERT_FALSE(map.addCityToRegion(0, 1));
		ASSERT_EQ(map.regionForCity(0), r0);
		// Add new region
		const auto r1 = map.addRegion();
		ASSERT_FALSE(r1 == r0);
		ASSERT_EQ(map.numRegions(), 2);
		ASSERT_EQ(map.regionCities(r1).size(), 0);
		// Add city to new region
		ASSERT_TRUE(map.addCityToRegion(0, r1));
		ASSERT_EQ(map.regionForCity(0), r1);
		ASSERT_EQ(map.regionCities(r1).size(), 1);
		ASSERT_EQ(map.regionCities(r0).size(), vCount - 1);
		// Remove cities
		map.removeCity(0);
		ASSERT_EQ(map.regionCities(r0).size() + map.regionCities(r1).size(), map.numCities());
	}

	/**
	*	@brief tests the functionality of Map object to compare against other Map objects
	*	@author Hrachya Hakobyan
	*/
	TEST_F(MapTest, compares){
		using namespace pan;
		Map m1, m2;
		const RoleIndex m1r0 = 0;
		auto m2r0 = m1r0;
		ASSERT_EQ(m1, m2);
		auto m1v0 = m1.addCity();
		ASSERT_NE(m1, m2);
		auto m2v0 = m2.addCity();
		ASSERT_EQ(m1, m2);
		m1.addConnection(m1v0, m1v0);
		ASSERT_NE(m1, m2);
		m2.addConnection(m2v0, m2v0);
		ASSERT_EQ(m1, m2);
		auto m1v1 = m1.addCity();
		ASSERT_NE(m1, m2);
		auto m2v1 = m2.addCity();
		ASSERT_EQ(m1, m2);
		auto m1r1 = m1.addRegion();
		ASSERT_NE(m1, m2);
		auto m2r1 = m2.addRegion();
		ASSERT_EQ(m1, m2);
		m1.addCityToRegion(m1v1, m1r1);
		ASSERT_NE(m1, m2);
		m2.addCityToRegion(m2v1, m2r1);
		ASSERT_EQ(m1, m2);
		m1.removeCity(m1v0);
		ASSERT_NE(m1, m2);
		m2.removeCity(m2v0);
		ASSERT_EQ(m1, m2);
		m1.removeRegion(m1r0);
		ASSERT_NE(m1, m2);
		m2.removeRegion(m2r0);
		ASSERT_EQ(m1, m2);
		m1.regionAt(m1r1).setName("Europe");
		ASSERT_NE(m1, m2);
		m2.regionAt(m2r1).setName("Europe");
		ASSERT_EQ(m1, m2);
	}

	/**
	*	@brief tests the functionality of Map class to serialize
	*	@author Hrachya Hakobyan
	*/
	TEST_F(MapTest, serializes){
		using namespace pan;
		using namespace detail;
		Map m;
		auto mv0 = m.addCity();
		m[mv0].setName("Atlanta");
		m[mv0].population = 1282341;
		m[mv0].researchStation = true;
		m[mv0].addPlayer(0);
		auto mv1 = m.addCity();
		m[mv1].setName("Montreal");
		m[mv1].population = 3134341;
		m.addConnection(mv0, mv1);
		auto mv2 = m.addCity();
		m[mv2].setName("London");
		m[mv2].population = 2981232;
		m[mv2].researchStation = true;
		m[mv2].addPlayer(1);
		m.addConnection(mv1, mv2);
		RoleIndex mr0 = 0;
		m.regionAt(mr0).setName("North American");
		auto mr1 = m.addRegion();
		m.regionAt(mr1).setName("Africa");
		auto mr2 = m.addRegion();
		m.regionAt(mr2).setName("Europe");
		m.addCityToRegion(mv1, mr1);
		m.addCityToRegion(mv2, mr2);

		std::string filename("temp/MapSerialization.xml");
		std::ofstream ofs(filename.c_str());
		ASSERT_TRUE(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		ASSERT_NO_THROW(oa << boost::serialization::make_nvp("Map", m));
		ofs.close();
	

		Map mNew;
		std::ifstream ifs(filename.c_str());
		ASSERT_TRUE(ifs.good());
		boost::archive::xml_iarchive ia(ifs);
		ASSERT_NO_THROW(ia >> boost::serialization::make_nvp("Map", mNew));
		ifs.close();
		ASSERT_TRUE(mNew == m);
	}

}