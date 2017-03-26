#include "stdafx.h"
#include "City.h"

namespace pan{

	City::City() :
		population(0),
		researchStation(false),
		xpos(0),
		ypos(0),
		region(0)
	{
	}

	City::City(const std::string& name, unsigned int population) :
		population(population),
		researchStation(false),
		name(name),
		xpos(0),
		ypos(0),
		region(0)
	{
	}

	City::City(const std::string& name, unsigned int population, double xpos, double ypos) :
		population(population),
		researchStation(false),
		name(name),
		xpos(xpos),
		ypos(ypos),
		region(0)
	{
	}

	City::City(const City& other) :
		population(other.population),
		researchStation(other.researchStation),
		players(other.players),
		name(other.name),
		cubes(other.cubes),
		xpos(other.xpos),
		ypos(other.ypos),
		region(other.region)
	{
	}

	City::City(City&& o) :
		population(o.population),
		researchStation(o.researchStation),
		name(std::move(o.name)),
		players(std::move(o.players)),
		cubes(std::move(o.cubes)),
		xpos(o.xpos),
		ypos(o.ypos),
		region(o.region)
	{
	}

	City& City::operator=(const City& o)
	{
		this->population = o.population;
		this->researchStation = o.researchStation;
		this->name = o.name;
		this->players = o.players;
		this->cubes = o.cubes;
		this->xpos = o.xpos;
		this->ypos = o.ypos;
		this->region = o.region;
		return *this;
	}

	City& City::operator=(City&& o)
	{
		this->population = o.population;
		this->researchStation = o.researchStation;
		this->name = std::move(o.name);
		this->players = std::move(o.players);
		this->cubes = std::move(o.cubes);
		this->xpos = o.xpos;
		this->ypos = o.ypos;
		this->region = o.region;
		return *this;
	}

	bool City::operator==(const City& other) const
	{
		return researchStation == other.researchStation &&
			population == other.population &&
			name == other.name &&
			players == other.players &&
			region == other.region &&
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
		std::string result = "City: " + name + ".\nRegion " + std::to_string(region) + ".\nPopulation: " + std::to_string(population)
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