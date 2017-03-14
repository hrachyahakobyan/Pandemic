#pragma once
#include "Settings.h"
#include "Disease.h"
#include "detail\Deck.h"
#include "Player.h"
#include "Role.h"
#include "Card.h"
#include "InfectionCard.h"

namespace pan{
	/**
	*	@brief container for game related data
	*	@author Hrachya Hakobyan
	*/
	struct GameData{
		GameData(const Settings& s);
		GameData(const GameData&);
		GameData& operator=(const GameData&);
		GameData(GameData&&);
		GameData& operator=(GameData&&);
		~GameData();

		bool operator==(const GameData&) const;
		bool operator!=(const GameData&) const;
		std::string description() const;

		Settings settings;
		unsigned int infectionRateMarker;
		unsigned int outbreakMarker;
		unsigned int researchStations;
		std::vector<Disease> diseases;
		std::vector<RegionIndex> diseaseCubes;
	};

	/**
	*	@brief container for player related data
	*	@author Hrachya Hakobyan
	*/
	struct PlayerData{
		PlayerData();
		PlayerData(const PlayerData&);
		PlayerData& operator=(const PlayerData&);
		PlayerData(PlayerData&&);
		PlayerData& operator=(PlayerData&&);
		~PlayerData();

		bool operator==(const PlayerData&) const;
		bool operator!=(const PlayerData&) const;
		std::string description() const;

		std::vector<std::shared_ptr<PlayerBase>> players;
		std::vector<bool> occupiedRoles;
	};

	/**
	*	@brief container for card related data
	*	@author Hrachya Hakobyan
	*/
	struct DeckData{
		DeckData();
		DeckData(const DeckData&);
		DeckData& operator=(const DeckData&);
		DeckData(DeckData&&);
		DeckData& operator=(DeckData&&);
		~DeckData();

		bool operator==(const DeckData&) const;
		bool operator!=(const DeckData&) const;
		std::string description() const;

		detail::Deck<std::shared_ptr<InfectionCard>> infectionDeck;
		detail::Deck<std::shared_ptr<InfectionCard>> infectionDiscardDeck;
		detail::Deck<std::shared_ptr<CardBase>> playerDeck;
		detail::Deck<std::shared_ptr<CardBase>> playerDiscardDeck;
	};
}



namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive & ar, pan::GameData & g, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(g.settings);
			ar & BOOST_SERIALIZATION_NVP(g.infectionRateMarker);
			ar & BOOST_SERIALIZATION_NVP(g.outbreakMarker);
			ar & BOOST_SERIALIZATION_NVP(g.researchStations);
			ar & BOOST_SERIALIZATION_NVP(g.diseases);
			ar & BOOST_SERIALIZATION_NVP(g.diseaseCubes);
		}

		template<class Archive>
		void serialize(Archive & ar, pan::DeckData & g, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(g.infectionDeck);
			ar & BOOST_SERIALIZATION_NVP(g.infectionDiscardDeck);
			ar & BOOST_SERIALIZATION_NVP(g.playerDeck);
			ar & BOOST_SERIALIZATION_NVP(g.playerDiscardDeck);
		}

		template<class Archive>
		void serialize(Archive & ar, pan::PlayerData & g, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(g.players);
			ar & BOOST_SERIALIZATION_NVP(g.occupiedRoles);
		}
	} // namespace serialization
} // namespace boost


