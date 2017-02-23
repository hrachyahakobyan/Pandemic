#include "stdafx.h"
#include "SerializationTest1.h"

/**
*	@brief tests the functionality of boost::serialization
*	@author Hrachya Hakobyan
*/
TEST_F(SerializationTest1, testComposite){
	std::string filename("temp/SerializationTest1.xml");
	std::ofstream ofs(filename.c_str());
	ASSERT_TRUE(ofs.good());
	boost::archive::xml_oarchive oa(ofs);
	oa << boost::serialization::make_nvp("A", aInitial);
	oa << boost::serialization::make_nvp("B", bInitial);
	oa << boost::serialization::make_nvp("D", dInitial);
	ofs.close();

	A aNew;
	B bNew;
	D dNew;
	std::ifstream ifs(filename.c_str());
	ASSERT_TRUE(ifs.good());
	boost::archive::xml_iarchive ia(ifs);
	ia >> boost::serialization::make_nvp("A", aNew);
	ia >> boost::serialization::make_nvp("B", bNew);
	ia >> boost::serialization::make_nvp("D", dNew);
	ifs.close();

	ASSERT_TRUE(aNew == aInitial);
	ASSERT_TRUE(bNew == bInitial);
}