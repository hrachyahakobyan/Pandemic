#include "stdafx.h"
#include "Settings.h"


namespace pan{
	Settings::Settings() :
		playerCount(2),
		epidemicCardCount(4),
		playerDrawCount(4),
		infectionRates({ 2, 2, 2, 3, 3, 4 })
	{
	}

	Settings::Settings(unsigned int pCount, unsigned int edCardCount,
		unsigned int playerDrawCount) :
		playerCount(pCount),
		epidemicCardCount(edCardCount),
		playerDrawCount(playerDrawCount),
		infectionRates({ 2, 2, 2, 3, 3, 4 })
	{
	}

	bool Settings::operator==(const Settings& s) const
	{
		return (playerCount == s.playerCount && epidemicCardCount == s.epidemicCardCount
			&&	playerDrawCount == s.playerDrawCount && discoverCureCardCount == s.discoverCureCardCount
			&& playerHandMax == s.playerHandMax && diseaseCubesPerDisease == s.diseaseCubesPerDisease
			&& maxResearchStations == s.maxResearchStations && outbreakMarkerMax == s.outbreakMarkerMax
			&& infectionRates == s.infectionRates);
	}

	bool Settings::operator!=(const Settings& s) const
	{
		return !((*this) == s);
	}
}
