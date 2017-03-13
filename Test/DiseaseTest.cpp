#include "stdafx.h"
#include "DiseaseTest.h"
#include "Disease.h"

TEST_F(DiseaseTest, changesState){
	using namespace pan;
	Disease d;
	ASSERT_EQ(d.getIsCured(), false);
	ASSERT_EQ(d.getIsEradicated(), false);

	d.setIsCured(false);
	d.setIsEradicated(false);
	ASSERT_EQ(d.getIsEradicated(), false);
	ASSERT_EQ(d.getIsCured(), false);

	d.setIsEradicated(true);
	ASSERT_EQ(d.getIsEradicated(), false);
	ASSERT_EQ(d.getIsCured(), false);

	d.setIsCured(true);
	ASSERT_EQ(d.getIsEradicated(), false);
	ASSERT_EQ(d.getIsCured(), true);

	d.setIsCured(false);
	ASSERT_EQ(d.getIsEradicated(), false);
	ASSERT_EQ(d.getIsCured(), false);

	d.setIsCured(true);
	d.setIsEradicated(true);
	ASSERT_EQ(d.getIsEradicated(), true);
	ASSERT_EQ(d.getIsCured(), true);

	d.setIsCured(false);
	ASSERT_EQ(d.getIsEradicated(), false);
	ASSERT_EQ(d.getIsCured(), false);

	d.setIsCured(true);
	d.setIsEradicated(true);
	d.setIsEradicated(true);
	ASSERT_EQ(d.getIsEradicated(), true);
	ASSERT_EQ(d.getIsCured(), true);

	d.setIsEradicated(false);
	ASSERT_EQ(d.getIsEradicated(), false);
	ASSERT_EQ(d.getIsCured(), true);

	d.setIsCured(false);
	ASSERT_EQ(d.getIsEradicated(), false);
	ASSERT_EQ(d.getIsCured(), false);
}

TEST_F(DiseaseTest, serializes)
{
	using namespace pan;
	std::vector<Disease> diseases;
	Disease d1(1);
	d1.setIsCured(true);
	diseases.push_back(d1);
	Disease d2(2);
	d2.setIsCured(true);
	d2.setIsEradicated(true);
	diseases.push_back(d2);
	Disease d3(3);
	diseases.push_back(d3);

	std::string filename("temp/DiseaseSerialization.xml");
	std::ofstream ofs(filename.c_str());
	ASSERT_TRUE(ofs.good());
	boost::archive::xml_oarchive oa(ofs);
	ASSERT_NO_THROW(oa << boost::serialization::make_nvp("Disease", diseases));
	ofs.close();

	std::vector<Disease> newDiseases;
	std::ifstream ifs(filename.c_str());
	ASSERT_TRUE(ifs.good());
	boost::archive::xml_iarchive ia(ifs);
	ASSERT_NO_THROW(ia >> boost::serialization::make_nvp("Disease", newDiseases));
	ifs.close();
	ASSERT_TRUE(diseases == newDiseases);
}