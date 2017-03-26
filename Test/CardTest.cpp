#include "stdafx.h"
#include "CardTest.h"
#include <core/FileManager.h>
namespace pan{


	TEST_F(CardTest, compares)
	{
		using namespace pan;
		/*InfectionCard inf(1);
		EpidemicCard ep;
		CityCard c(1);
		EventCard e(EventType::Airlift);
		EventCard e2(EventType::GovGrant);

		ASSERT_EQ(inf, inf);
		ASSERT_EQ(ep, ep);
		ASSERT_EQ(c, c);
		ASSERT_EQ(e, e);
		ASSERT_EQ(e2, e2);

		InfectionCard inf2(2);
		CityCard c2(2);
		ASSERT_NE(inf, inf2);
		ASSERT_NE(c, c2);
		ASSERT_NE(e, e2);

		CardBase& base1 = inf;
		CardBase& base2 = ep;
		CardBase& base3 = c;
		CardBase& base4 = e;
		CardBase& base5 = e2;
		CardBase& base6 = inf2;
		CardBase& base7 = c2;

		ASSERT_NE(base1, base2);
		ASSERT_NE(base2, base3);
		ASSERT_NE(base3, base4);
		ASSERT_NE(base4, base5);
		ASSERT_NE(base5, base6);
		ASSERT_NE(base6, base7);
		ASSERT_NE(base1, base6);
		ASSERT_NE(base4, base5);
		ASSERT_NE(base3, base7);

		ASSERT_EQ(base1, base1);
		ASSERT_EQ(base2, base2);
		ASSERT_EQ(base3, base3);
		ASSERT_EQ(base4, base4);*/
	}

	TEST_F(CardTest, serializes)
	{
		using namespace pan;
		std::vector<std::shared_ptr<CardBase>> cards;
		cards.push_back(std::make_shared<InfectionCard>(0));
		cards.push_back(std::make_shared<EpidemicCard>());
		cards.push_back(std::shared_ptr<CityCard>(new CityCard(1, 0)));
		cards.push_back(std::make_shared<EventCard>(EventType::Airlift));
		cards.push_back(std::make_shared<EventCard>(EventType::GovGrant));

		ASSERT_TRUE(FileManager::getInstance().save(cards, "CardSerialization.xml", "temp", true));
		std::vector<std::shared_ptr<CardBase>> newCards;
		ASSERT_TRUE(FileManager::getInstance().load(newCards, "CardSerialization.xml", "temp"));

		ASSERT_EQ(cards.size(), newCards.size());
		for (std::size_t i = 0; i < cards.size(); i++){
				ASSERT_EQ(*cards[i], *newCards[i]);
		}
	}
}