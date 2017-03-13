#include "stdafx.h"
#include "Settings.h"


namespace pan{
	Settings::Settings() :
		playerCount(2),
		epidemicCardCount(4),
		playerDrawCount(4),
		discoverCureCardCount(5),
		playerHandMax(7)
	{
	}

	Settings::Settings(unsigned int pCount, unsigned int edCardCount,
		unsigned int playerDrawCount, unsigned int disCureCCount,
		unsigned int playerHandMax) :
		playerCount(pCount),
		epidemicCardCount(edCardCount),
		playerDrawCount(playerDrawCount),
		discoverCureCardCount(disCureCCount),
		playerHandMax(playerHandMax)
	{
	}

	bool Settings::operator==(const Settings& s) const
	{
		return (playerCount == s.playerCount && epidemicCardCount == s.epidemicCardCount
			&&	playerDrawCount == s.playerDrawCount && discoverCureCardCount == s.discoverCureCardCount
			&& playerHandMax == s.playerHandMax);
	}

	bool Settings::operator!=(const Settings& s) const
	{
		return !((*this) == s);
	}
}
