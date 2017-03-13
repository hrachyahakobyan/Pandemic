#pragma once
#include "Object.h"

namespace pan{
	class Settings : public Object
	{
	public:
		Settings();
		Settings(unsigned int playerCount, unsigned int epidemicCardCount, 
				unsigned int playerDrawCount, unsigned int discoverCureCardCount = 5,
				unsigned int playerHandMax = 7);
		~Settings() = default;

		inline static Settings Beginner(unsigned int players);
		inline static Settings Standard(unsigned int players);
		inline static Settings Heroic(unsigned int players);

		const unsigned int playerCount;
		const unsigned int epidemicCardCount;
		const unsigned int playerDrawCount;
		const unsigned int discoverCureCardCount;
		const unsigned int playerHandMax;

		inline std::string description() const;

		bool operator==(const Settings&) const;
		bool operator!=(const Settings&) const;

	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object);
			ar & boost::serialization::make_nvp("playerCount", const_cast<unsigned int&>(playerCount));
			ar & boost::serialization::make_nvp("epidemicCardCount", const_cast<unsigned int&>(epidemicCardCount));
			ar & boost::serialization::make_nvp("playerDrawCount", const_cast<unsigned int&>(playerDrawCount));
			ar & boost::serialization::make_nvp("discoverCureCardCount", const_cast<unsigned int&>(discoverCureCardCount));
			ar & boost::serialization::make_nvp("playerHandMax", const_cast<unsigned int&>(playerHandMax));
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

	std::string Settings::description() const
	{
		return "Number of cards drawn by a player: " + std::to_string(playerDrawCount) + "\n Epidemic Card Count: " + std::to_string(epidemicCardCount)
			+ "\n Player Count: " + std::to_string(playerCount) + "\n Cards required to discover a cure: " + std::to_string(discoverCureCardCount)
			+ "Maximum allowed cards in a hand: " + std::to_string(playerHandMax);
	}
}

