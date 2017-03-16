#include "stdafx.h"
#include "PlayerTest.h"

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

		medic.cards.push(std::shared_ptr<CardBase>(new CityCard(2)));
		ASSERT_NE(medic, medic2);

		medic2.cards.push(std::shared_ptr<CardBase>(new CityCard(2)));
		ASSERT_EQ(medic, medic2);

		medic.cards.clear();
		medic.cards.push(std::shared_ptr<CardBase>(new EpidemicCard()));
		ASSERT_NE(medic, medic2);

		medic2.cards.clear();
		ASSERT_NE(medic, medic2);
	}

	/**
	*	@brief tests the functionality of Player class to serialize
	*	@author Hrachya Hakobyan
	*/
	TEST_F(PlayerTest, serializes){

		using namespace pan;
		PlayerBase* medic = new Medic();
		medic->setName("John");
		medic->setLocation(1);
		medic->cards.push(std::shared_ptr<CardBase>(new EpidemicCard()));
		medic->cards.push(std::shared_ptr<CardBase>(new CityCard(1)));
		medic->cards.push(std::shared_ptr<CardBase>(new EventCard(EventType::GovGrant)));

		std::string filename("temp/PlayerSerialization.xml");
		std::ofstream ofs(filename.c_str());
		ASSERT_TRUE(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		registerTypes(oa);
		ASSERT_NO_THROW(oa << boost::serialization::make_nvp("Player", medic));
		ofs.close();

		PlayerBase* newPlayer = nullptr;
		std::ifstream ifs(filename.c_str());
		ASSERT_TRUE(ifs.good());
		boost::archive::xml_iarchive ia(ifs);
		registerTypes(ia);
		ia >> boost::serialization::make_nvp("Player", newPlayer);
		ifs.close();
		ASSERT_TRUE(newPlayer != nullptr);
		ASSERT_TRUE(*medic == (*newPlayer));
		delete newPlayer;
		delete medic;
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
		players[0]->cards.push(std::shared_ptr<CardBase>(new EpidemicCard()));
		players[1]->cards.push(std::shared_ptr<CardBase>(new CityCard(2)));
		players[2]->cards.push(std::shared_ptr<CardBase>(new EventCard(EventType::Forecast)));
		players[3]->cards.push(std::shared_ptr<CardBase>(new EventCard(EventType::OneQuietNight)));

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
