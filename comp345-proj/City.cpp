#include "stdafx.h"
#include "City.h"

namespace pan{

	City::City() :
		population(0),
		researchStation(false)
	{
	}

	City::City(const std::string& name, unsigned int population) :
		population(population),
		researchStation(false),
		name(name)
	{
	}

	City::City(const City& other) :
		population(other.population),
		researchStation(other.researchStation),
		players(other.players),
		name(other.name),
		cubes(other.cubes)
	{
	}

	City::City(City&& o) :
		population(o.population),
		researchStation(o.researchStation),
		name(std::move(o.name)),
		players(std::move(o.players)),
		cubes(std::move(o.cubes))
	{
	}

	City& City::operator=(const City& o)
	{
		this->population = o.population;
		this->researchStation = o.researchStation;
		this->name = o.name;
		this->players = o.players;
		this->cubes = o.cubes;
		return *this;
	}

	City& City::operator=(City&& o)
	{
		this->population = o.population;
		this->researchStation = o.researchStation;
		this->name = std::move(o.name);
		this->players = std::move(o.players);
		this->cubes = std::move(o.cubes);
		return *this;
	}

	bool City::operator==(const City& other) const
	{
		return researchStation == other.researchStation &&
			population == other.population &&
			name == other.name &&
			players == other.players &&
			cubes == other.cubes;
	}

	std::size_t City::getCubes(DiseaseType r) const
	{
		if (r + 1 > cubes.size()){
			return 0;
		}
		return cubes[r];
	}

	void City::setCubes(DiseaseType r, std::size_t cubeCount)
	{
		if (r + 1 > cubes.size()){
			std::size_t toAdd = (r - cubes.size() + 1);
			for (std::size_t i = 0; i < toAdd; i++)
				cubes.push_back(0);
		}
		cubes[r] = cubeCount;
	}

	std::string City::description() const
	{
		std::string result = "City: " + name + ".\nPopulation: " + std::to_string(population)
			+ "\nResearch station: " + std::to_string(researchStation) + "\nCubes: ";
		for (std::size_t i = 0; i < cubes.size(); i++){
			result += "\t Region: " + std::to_string(i) + " cubes: " + std::to_string(cubes[i]) + '\n';
		}
		result += "\nPlayers: ";
		for (const auto& p : players){
			result += "\t" + p + '\n';
		}
		return result;
	}
}