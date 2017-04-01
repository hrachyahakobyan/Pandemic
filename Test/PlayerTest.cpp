#include "stdafx.h"
#include "PlayerTest.h"
#include <core/FileManager.h>

namespace pan{
	/**
	*	@brief tests the functionality of Player objects to compare against other Player objects
	*	@author Hrachya Hakobyan
	*/
	TEST_F(PlayerTest, compares){
		using namespace pan;
		Medic medic(0);
		medic.setName("John");
		ASSERT_EQ(medic, medic);
		PlayerBase& medicRef = medic;
		ASSERT_EQ(medicRef, medic);
		ASSERT_EQ(medicRef, medicRef);
		Medic medic2(0);
		ASSERT_NE(medic, medic2);
		medic2.setName("John");
		ASSERT_EQ(medic2, medic);

		Dispatcher dispatcher(0);
		ASSERT_NE(dispatcher, medic);
		PlayerBase& dispatcherRef = dispatcher;
		ASSERT_NE(dispatcherRef, medicRef);
		dispatcher.setName("John");
		ASSERT_NE(dispatcher, medic);

		medic.setLocation(1);
		ASSERT_NE(medic, medic2);
		medic2.setLocation(1);
		ASSERT_EQ(medic, medic2);

		medic.cards.push(std::shared_ptr<CardBase>(new CityCard(2, 0)));
		ASSERT_NE(medic, medic2);

		medic2.cards.push(std::shared_ptr<CardBase>(new CityCard(2, 0)));
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
		PlayerBase* medic = new Medic(0);
		medic->setName("John");
		medic->setLocation(1);
		medic->cards.push(std::shared_ptr<CardBase>(new EpidemicCard()));
		medic->cards.push(std::shared_ptr<CardBase>(new CityCard(1, 0)));
		medic->cards.push(std::shared_ptr<CardBase>(new EventCard(EventType::GovGrant)));

		ASSERT_TRUE(FileManager::getInstance().save(medic, "PlayerSerialization.xml", "temp", true));

		PlayerBase* newPlayer = nullptr;
		ASSERT_TRUE(FileManager::getInstance().load(newPlayer, "PlayerSerialization.xml", "temp"));
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
		/*std::vector<std::shared_ptr<PlayerBase>> players;
		players.push_back(std::shared_ptr<PlayerBase>(new Medic("John")));
		players.push_back(std::shared_ptr<PlayerBase>(new Medic("Jack")));
		players.push_back(std::shared_ptr<PlayerBase>(new Dispatcher("Eric")));
		players.push_back(std::shared_ptr<PlayerBase>(new Researcher("Anton")));
		players[0]->setLocation(1);
		players[1]->setLocation(2);
		players[2]->setLocation(3);
		players[3]->setLocation(4);
		players[0]->cards.push(std::shared_ptr<CardBase>(new EpidemicCard()));
		players[1]->cards.push(std::shared_ptr<CardBase>(new CityCard(2, 0)));
		players[2]->cards.push(std::shared_ptr<CardBase>(new EventCard(EventType::Forecast)));
		players[3]->cards.push(std::shared_ptr<CardBase>(new EventCard(EventType::OneQuietNight)));

		ASSERT_TRUE(FileManager::getInstance().save(players, "PlayerSerializationContainer.xml", "temp", true));
		std::vector<std::shared_ptr<PlayerBase>> newPlayers;
		ASSERT_TRUE(FileManager::getInstance().load(newPlayers, "PlayerSerializationContainer.xml", "temp"));

		ASSERT_EQ(players.size(), newPlayers.size());
		for (std::size_t i = 0; i < players.size(); i++){
			ASSERT_EQ(*players[i], *newPlayers[i]);
		}*/
	}
}
