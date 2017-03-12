#include "stdafx.h"
#include "PlayerTest.h"
#include "common.h"

namespace pan{
	/**
	*	@brief tests the functionality of Player objects to compare against other Player objects
	*	@author Hrachya Hakobyan
	*/
	TEST_F(PlayerTest, compares){
		using namespace pan;
		Medic medic;
		medic.setName("John");
		ASSERT_EQ(medic, medic);
		PlayerBase& medicRef = medic;
		ASSERT_EQ(medicRef, medic);
		ASSERT_EQ(medicRef, medicRef);
		Medic medic2;
		ASSERT_NE(medic, medic2);
		medic2.setName("John");
		ASSERT_EQ(medic2, medic);

		Dispatcher dispatcher;
		ASSERT_NE(dispatcher, medic);
		PlayerBase& dispatcherRef = dispatcher;
		ASSERT_NE(dispatcherRef, medicRef);
		dispatcher.setName("John");
		ASSERT_NE(dispatcher, medic);

		medic.setLocation(1);
		ASSERT_NE(medic, medic2);
		medic2.setLocation(1);
		ASSERT_EQ(medic, medic2);
	}

	/**
	*	@brief tests the functionality of Player class to serialize
	*	@author Hrachya Hakobyan
	*/
	TEST_F(PlayerTest, serializes){

		using namespace pan;
		Medic medic;
		medic.setName("John");
		medic.setLocation(1);
		
		std::string filename("temp/PlayerSerialization.xml");
		std::ofstream ofs(filename.c_str());
		ASSERT_TRUE(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		ASSERT_NO_THROW(oa << boost::serialization::make_nvp("Player", medic));
		ofs.close();

		PlayerBase* newPlayer = nullptr;
		std::ifstream ifs(filename.c_str());
		ASSERT_TRUE(ifs.good());
		boost::archive::xml_iarchive ia(ifs);
		ia.template register_type<pan::Player<Roles::Medic>>();
		ASSERT_NO_THROW(ia >> boost::serialization::make_nvp("Player", newPlayer));
		ifs.close();
		ASSERT_TRUE(newPlayer != nullptr);
		ASSERT_TRUE(medic == (*newPlayer));
		delete newPlayer;
	}

	/**
	*	@brief tests the functionality of Player class to serialize
	*	@author Hrachya Hakobyan
	*/
	TEST_F(PlayerTest, serializesContainer){

		using namespace pan;
		std::vector<std::shared_ptr<PlayerBase>> players;
		players.push_back(std::shared_ptr<PlayerBase>(new Medic("John")));
		players.push_back(std::shared_ptr<PlayerBase>(new Medic("Jack")));
		players.push_back(std::shared_ptr<PlayerBase>(new Dispatcher("Eric")));
		players.push_back(std::shared_ptr<PlayerBase>(new Researcher("Anton")));
		players[0]->setLocation(1);
		players[1]->setLocation(2);
		players[2]->setLocation(3);
		players[3]->setLocation(4);

		std::string filename("temp/PlayerSerialization2.xml");
		std::ofstream ofs(filename.c_str());
		ASSERT_TRUE(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		registerTypes(oa);
		ASSERT_NO_THROW(oa << boost::serialization::make_nvp("Players", players));
		ofs.close();

		std::vector<std::shared_ptr<PlayerBase>> newPlayers;
		std::ifstream ifs(filename.c_str());
		ASSERT_TRUE(ifs.good());
		boost::archive::xml_iarchive ia(ifs);
		registerTypes(ia);
		ASSERT_NO_THROW(ia >> boost::serialization::make_nvp("Players", newPlayers));
		ifs.close();
		
		ASSERT_EQ(players.size(), newPlayers.size());
		for (std::size_t i = 0; i < players.size(); i++){
			ASSERT_EQ(*players[i], *newPlayers[i]);
		}
	}
}
