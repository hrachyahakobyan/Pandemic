#include "stdafx.h"
#include "Settings.h"


namespace pan{
	Settings::Settings() :
		playerCount(2),
		epidemicCardCount(4),
		initialCards(4),
		infectionRates({ 2, 2, 2, 3, 3, 4 })
	{
	}

	Settings::Settings(unsigned int pCount, unsigned int edCardCount,
		unsigned int initialCards) :
		playerCount(pCount),
		epidemicCardCount(edCardCount),
		initialCards(initialCards),
		infectionRates({ 2, 2, 2, 3, 3, 4 })
	{
	}

	bool Settings::operator==(const Settings& s) const
	{
		return (playerCount == s.playerCount && epidemicCardCount == s.epidemicCardCount
			&&	playerDrawCount == s.playerDrawCount && discoverCureCardCount == s.discoverCureCardCount
			&& playerHandMax == s.playerHandMax && diseaseCubesPerDisease == s.diseaseCubesPerDisease
			&& maxResearchStations == s.maxResearchStations && outbreakMarkerMax == s.outbreakMarkerMax
			&& infectionRates == s.infectionRates && initialCards == s.initialCards);
	}

	bool Settings::operator!=(const Settings& s) const
	{
		return !((*this) == s);
	}
}
