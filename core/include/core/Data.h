#pragma once
#include "Settings.h"
#include "Disease.h"
#include "detail\Deck.h"
#include "Player.h"
#include "Role.h"
#include "Cards.h"

namespace pan{
	/**
	*	@brief describes the game state.
	*	@author Hrachya Hakobyan
	*/
	enum class GameState : unsigned int{
		InProgress = 0, Victory, Defeat
	};

	static const std::map<GameState, std::string> GameStateDescriptions{
		{GameState::InProgress, "In Progress"},
		{GameState::Victory, "Victory"},
		{GameState::Defeat, "Defeat"}
	};

	/**
	*	@brief container for game related data
	*	@author Hrachya Hakobyan
	*/
	struct GameData{
		GameData();
		GameData(const Settings& s);
		GameData(const GameData&);
		GameData& operator=(const GameData&);
		GameData(GameData&&);
		GameData& operator=(GameData&&);
		~GameData();

		bool operator==(const GameData&) const;
		bool operator!=(const GameData&) const;
		std::string description() const;

		/**
		*	The game settings
		*/
		Settings settings;
		/**
		*	Whether the game was initialized
		*/
		bool initialized;
		/**
		*	The current state of the game
		*/
		GameState state;
		unsigned int infectionRateMarker;
		unsigned int outbreakMarker;
		unsigned int researchStations;
		std::vector<Disease> diseases;
		/**
		*	The available disease cubes
		*/
		std::vector<RegionIndex> diseaseCubes;
		/**
		*	The disease cubes that have been removed from the game
		*/
		std::vector<RegionIndex> removedDiseasesCubes;
	};

	/**
	*	@brief describes the current stage of the player turn.
	*	Act = the player still needs to perform actions
	*	Draw = the player needs to draw cards
	*	Infect = the player needs to infect cities
	*	Discard = the player has to discard some cards
	*/
	enum class PlayerStage : unsigned int{
		Act = 0, Draw, Infect, Discard
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

		/**
		*	The current player turn
		*/
		PlayerIndex turn;
		/**
		*	The current player stage
		*/
		PlayerStage stage;
		/**
		*	The previous stage
		*/
		PlayerStage prevStage;
		/**
		*	How many actions the player has already committed in the Act stage
		*/
		unsigned int actionCounter;
		std::vector<std::shared_ptr<PlayerBase>> players;
		/**
		*	Stores information about roles being occupied.
		*	If i-the value is true, then the i-th role has already been taken
		*/
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
		detail::Deck<CardBasePtr> playerDeck;
		detail::Deck<CardBasePtr> playerDiscardDeck;
	};
}



namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive & ar, pan::GameData & g, const unsigned int version)
		{
			ar.template register_type<pan::Settings>();
			ar.template register_type<pan::Disease>();
			ar & BOOST_SERIALIZATION_NVP(g.settings);
			ar & BOOST_SERIALIZATION_NVP(g.infectionRateMarker);
			ar & BOOST_SERIALIZATION_NVP(g.outbreakMarker);
			ar & BOOST_SERIALIZATION_NVP(g.researchStations);
			ar & BOOST_SERIALIZATION_NVP(g.diseases);
			ar & BOOST_SERIALIZATION_NVP(g.diseaseCubes);
			ar & BOOST_SERIALIZATION_NVP(g.removedDiseasesCubes);
			ar & BOOST_SERIALIZATION_NVP(g.state);
			ar & BOOST_SERIALIZATION_NVP(g.initialized);
		}

		template<class Archive>
		void serialize(Archive & ar, pan::DeckData & g, const unsigned int version)
		{
			ar.template register_type<pan::Settings>();
			ar.template register_type<pan::InfectionCard>(); 
			ar.template register_type<pan::EpidemicCard>(); 
			ar.template register_type<pan::EventCard>(); 
			ar.template register_type<pan::CityCard>(); 
			ar & BOOST_SERIALIZATION_NVP(g.infectionDeck);
			ar & BOOST_SERIALIZATION_NVP(g.infectionDiscardDeck);
			ar & BOOST_SERIALIZATION_NVP(g.playerDeck);
			ar & BOOST_SERIALIZATION_NVP(g.playerDiscardDeck);
		}

		template<class Archive>
		void serialize(Archive & ar, pan::PlayerData & g, const unsigned int version)
		{
			ar.template register_type<pan::Dispatcher>();
			ar.template register_type<pan::OperationsExpert>();
			ar.template register_type<pan::Scientist>();
			ar.template register_type<pan::Medic>();
			ar.template register_type<pan::QSpecialist>();
			ar.template register_type<pan::Researcher>();
			ar.template register_type<pan::CPlanner>();
			ar & BOOST_SERIALIZATION_NVP(g.actionCounter);
			ar & BOOST_SERIALIZATION_NVP(g.turn);
			ar & BOOST_SERIALIZATION_NVP(g.stage);
			ar & BOOST_SERIALIZATION_NVP(g.prevStage);
			ar & BOOST_SERIALIZATION_NVP(g.players);
			ar & BOOST_SERIALIZATION_NVP(g.occupiedRoles);
		}
	} // namespace serialization
} // namespace boost


