#include "stdafx.h"
#include "City.h"

namespace pan{

	City::City() :
		population(0),
		researchStation(false)
	{
	}

	City::City(const std::string& name) :
		population(0),
		researchStation(false),
		name(name)
	{
	}

	City::City(const City& other) :
		population(other.population),
		researchStation(other.researchStation),
		players(other.players),
		name(other.name)
	{
	}

	City::City(City&& o) :
		population(o.population),
		researchStation(o.researchStation),
		name(std::move(o.name)),
		players(std::move(o.players))
	{
	}

	City& City::operator=(const City& o)
	{
		this->population = o.population;
		this->researchStation = o.researchStation;
		this->name = o.name;
		this->players = o.players;
		return *this;
	}

	City& City::operator=(City&& o)
	{
		this->population = o.population;
		this->researchStation = o.researchStation;
		this->name = std::move(o.name);
		this->players = std::move(o.players);
		return *this;
	}

	bool City::operator==(const City& other) const
	{
		return researchStation == other.researchStation &&
			population == other.population &&
			name == other.name &&
			players == other.players;
	}
}