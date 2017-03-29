#pragma once

namespace pan{
	typedef int PlayerIndex;
	typedef unsigned int RegionIndex;
	typedef unsigned int RoleIndex;
	typedef RegionIndex DiseaseType;
	typedef std::size_t CityIndex;
}

#define REGISTER_TYPES(ARCHIVE) \
	ARCHIVE.template register_type<pan::PlayerBase>(); \
	ARCHIVE.template register_type<pan::Dispatcher>(); \
	ARCHIVE.template register_type<pan::FOperative>(); \
	ARCHIVE.template register_type<pan::Generalist>(); \
	ARCHIVE.template register_type<pan::Medic>(); \
	ARCHIVE.template register_type<pan::QSpecialist>(); \
	ARCHIVE.template register_type<pan::Researcher>(); \
	ARCHIVE.template register_type<pan::InfectionCard>(); \
	ARCHIVE.template register_type<pan::EpidemicCard>(); \
	ARCHIVE.template register_type<pan::EventCard>(); \
	ARCHIVE.template register_type<pan::CityCard>(); \
	ARCHIVE.template register_type<pan::CardBase>(); \
	ARCHIVE.template register_type<pan::Settings>(); \
	ARCHIVE.template register_type<pan::detail::Deck<pan::CardBase>>();


#define FRIEND_TESTS FRIEND_TEST(ActionTest, Infect); \
	FRIEND_TEST(ActionTest, Outbreak); \
	FRIEND_TEST(ActionTest, Move); \
	FRIEND_TEST(ActionTest, BuildResearchStation); \
	FRIEND_TEST(ActionTest, BuildResearchStation); \
	FRIEND_TEST(CardTest, serializes); \
	FRIEND_TEST(ActionTest, BuildResearchStation); \
	FRIEND_TEST(DeckTest, Constructs); \
	FRIEND_TEST(DeckTest, Pushes); \
	FRIEND_TEST(DeckTest, Pops); \
	FRIEND_TEST(DeckTest, Deals); \
	FRIEND_TEST(DeckTest, Serializes); \
	FRIEND_TEST(DiseaseTest, changesState); \
	FRIEND_TEST(DiseaseTest, serializes); \
	FRIEND_TEST(FactoryTest, registers); \
	FRIEND_TEST(FactoryTest, constructs); \
	FRIEND_TEST(FileManagerTest, createsDirectory); \
	FRIEND_TEST(FileManagerTest, createsFile); \
	FRIEND_TEST(FileManagerTest, savesGame); \
	FRIEND_TEST(FileManagerTest, getsSavedGames); \
	FRIEND_TEST(GameplayTest, Test1); \
	FRIEND_TEST(GraphTest, inserts); \
	FRIEND_TEST(GraphTest, removes); \
	FRIEND_TEST(GraphTest, clears); \
	FRIEND_TEST(GraphTest, edges); \
	FRIEND_TEST(GraphTest, neighbors); \
	FRIEND_TEST(GraphTest, serializes); \
	FRIEND_TEST(MapTest, addsRemovesCity); \
	FRIEND_TEST(MapTest, addsRemovesConnections); \
	FRIEND_TEST(MapTest, addsRemovesRegions); \
	FRIEND_TEST(MapTest, assignsRegions); \
	FRIEND_TEST(MapTest, compares); \
	FRIEND_TEST(MapTest, serializes); \
	FRIEND_TEST(NotificationCenterTest, Test1); \
	FRIEND_TEST(OutbreakTest, Test1); \
	FRIEND_TEST(OutbreakTest, Test2); \
	FRIEND_TEST(PlayerTest, compares); \
	FRIEND_TEST(PlayerTest, serializes); \
	FRIEND_TEST(PlayerTest, serializesContainer); \
	friend class ActionTest;