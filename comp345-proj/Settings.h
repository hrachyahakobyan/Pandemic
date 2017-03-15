#pragma once
#include "Object.h"

namespace pan{
	/**
	*	@brief encapsulates all game related parameters.
	*	@author Hrachya Hakobyan
	*/
	class Settings : public Object
	{
	public:
		Settings();
		Settings(unsigned int playerCount, unsigned int epidemicCardCount, 
			unsigned int initialCards);
		~Settings() = default;

		inline static Settings Beginner(unsigned int players);
		inline static Settings Standard(unsigned int players);
		inline static Settings Heroic(unsigned int players);

		/**
		*	Number of players
		*/
		unsigned int playerCount;
		/**
		*	Number of epidemic cards
		*/
		unsigned int epidemicCardCount;
		/**
		*	Initial number of cards of each player
		*/
		unsigned int initialCards;
		/**
		*	Number of cards to be drawn by each player
		*/
		unsigned int playerDrawCount = 2;
		/**
		*	Default number of matching cards required to cure a disease
		*/
		unsigned int discoverCureCardCount = 5;
		/**
		*	Size of the player hand
		*/
		unsigned int playerHandMax = 7;
		/**
		*	Number of disease cubes per disease
		*/
		unsigned int diseaseCubesPerDisease = 24;
		/**
		*	Maximum number of research stations
		*/
		unsigned int maxResearchStations = 6;
		/**
		*	Maximum value of the outbreak marker
		*/
		unsigned int outbreakMarkerMax = 8;
		/**
		*	The infection rates for a give infection rate marker
		*/
		std::vector<unsigned int> infectionRates; 

		inline std::string description() const;

		bool operator==(const Settings&) const;
		bool operator!=(const Settings&) const;

	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object);
			ar & BOOST_SERIALIZATION_NVP(initialCards);
			ar & BOOST_SERIALIZATION_NVP(playerCount);
			ar & BOOST_SERIALIZATION_NVP(epidemicCardCount);
			ar & BOOST_SERIALIZATION_NVP(playerDrawCount);
			ar & BOOST_SERIALIZATION_NVP(discoverCureCardCount);
			ar & BOOST_SERIALIZATION_NVP(playerHandMax);
			ar & BOOST_SERIALIZATION_NVP(diseaseCubesPerDisease);
			ar & BOOST_SERIALIZATION_NVP(maxResearchStations);
			ar & BOOST_SERIALIZATION_NVP(outbreakMarkerMax);
			ar & BOOST_SERIALIZATION_NVP(infectionRates);
		}
	};

	Settings Settings::Beginner(unsigned int players)
	{
		assert(players >= 2 && players <= 4 && "Invalid player count");
		return Settings(players, 4, 4 - (players - 2));
	}

	Settings Settings::Standard(unsigned int players)
	{
		assert(players >= 2 && players <= 4 && "Invalid player count");
		return Settings(players, 5, 4 - (players - 2));
	}

	Settings Settings::Heroic(unsigned int players)
	{
		assert(players >= 2 && players <= 4 && "Invalid player count");
		return Settings(players, 6, 4 - (players - 2));
	}
#pragma message ("Not all members included in description")
	std::string Settings::description() const
	{
		return "Initial cards: " + std::to_string(initialCards) + "\n Epidemic Card Count: " + std::to_string(epidemicCardCount)
			+ "\n Player Count: " + std::to_string(playerCount) + "\n Cards required to discover a cure: " + std::to_string(discoverCureCardCount)
			+ "\n Maximum allowed cards in a hand: " + std::to_string(playerHandMax);
	}
}

