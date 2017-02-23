#include "stdafx.h"
#include "SerializationTest2.h"
#include <memory>

/**
*	@brief tests the functionality of boost::serialization to serialize shared_ptr
*	@author Hrachya Hakobyan
*/
TEST_F(SerializationTest2, testSharedPtr){

	std::shared_ptr<A> a1(new A());
	std::shared_ptr<A> a2(new B());
	std::shared_ptr<A> a3 = a1;
	std::shared_ptr<A> a4 = a2;

	a3.get()->name = "A1";

	c1Initial.objs.push_back(a1);
	c1Initial.objs.push_back(a2);
	c1Initial.objs.push_back(a3);
	c1Initial.objs.push_back(a4);

	c2Initial.objs.push_back(a1);
	c2Initial.objs.push_back(a2);
	c2Initial.objs.push_back(a3);
	c2Initial.objs.push_back(a4);

	a1.reset();
	a2.reset();
	a3.reset();
	a4.reset();

	ASSERT_TRUE(c1Initial == c2Initial);

	std::string filename("temp/SerializationTest2.xml");
	std::ofstream ofs(filename.c_str());
	ASSERT_TRUE(ofs.good());
	boost::archive::xml_oarchive oa(ofs);
	oa << boost::serialization::make_nvp("C1", c1Initial);
	oa << boost::serialization::make_nvp("C2", c2Initial);
	ofs.close();

	C c1New, c2New;
	std::ifstream ifs(filename.c_str());
	ASSERT_TRUE(ifs.good());
	boost::archive::xml_iarchive ia(ifs);
	ia >> boost::serialization::make_nvp("C1", c1New);
	ia >> boost::serialization::make_nvp("C2", c2New);
	ifs.close();

	ASSERT_TRUE(c1New == c2New);
}
