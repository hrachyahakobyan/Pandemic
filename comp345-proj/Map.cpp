#include "stdafx.h"
#include "Map.h"


namespace pan{

	Map::Map() 
	{
		regionMap.insert({ 0, Region() });
	}

	Map::Map(const Region& r) 
	{
		regionMap.insert({ 0, r });
	}

	Map::Map(Map&& o) :
		graph(std::move(o.graph)),
		regionMap(std::move(o.regionMap)),
		cityRegionMap(std::move(o.cityRegionMap))
	{
	}

	Map::Map(const Map& o) :
		graph(o.graph),
		regionMap(o.regionMap),
		cityRegionMap(o.cityRegionMap)
	{
	}

	Map& Map::operator=(const Map& o)
	{
		this->graph = o.graph;
		this->regionMap = o.regionMap;
		this->cityRegionMap = o.cityRegionMap;
		return *this;
	}

	Map& Map::operator=(Map&& o)
	{
		this->graph = std::move(o.graph);
		this->regionMap = std::move(o.regionMap);
		this->cityRegionMap = std::move(o.cityRegionMap);
		return *this;
	}

	bool Map::operator==(const Map& other) const
	{
		if (!(graph == other.graph && regionMap == other.regionMap 
			&& cityRegionMap == other.cityRegionMap && regionMap == other.regionMap))
			return false;
		std::size_t cityCount = numCities();
		for (std::size_t i = 0; i < cityCount; i++){
			if (this->operator[](i) != other[i])
				return false;
		}
		return true;
	}

	std::string Map::description() const
	{
		std::string res = "Map. Cities: " + std::to_string(this->numCities()) + '\n';
		res += "Connections: " + std::to_string(this->numConnections()) + '\n';
		res += "Regions: " + std::to_string(this->numRegions()) + '\n';
		return res;
	}

	Map::CityIndex Map::addCity(const City& city)
	{
		auto ci = graph.addVertex(city);
		bool addRegion = addCityToRegion(ci, regionMap.begin()->first);
#ifdef _DEBUG
		assert(addRegion && "ERROR pan::Map::CityIndex addCity(const City&): Could not add city to region");
#endif
		return ci;
	}

	void Map::removeCity(Map::CityIndex i)
	{
		if (graph.vertexExists(i)){
			cityRegionMap.erase(cityRegionMap.find(i));
		}
		graph.removeVertex(i);
	}

	std::vector<RegionIndex> Map::getRegions() const
	{
		std::vector<RegionIndex> regions;
		for (const auto& p : regionMap){
			regions.push_back(p.first);
		}
		return regions;
	}

	RegionIndex Map::regionForCity(CityIndex i) const
	{
		if (!(i >= 0 && i < graph.numVertices()))
			throw std::exception("ERROR pan::Map::const Region& region(CityIndex). Invalid index");
		auto cityIt = cityRegionMap.find(i);
		if (cityIt == cityRegionMap.end())
			throw std::exception("ERROR pan::Map::const Region& region(CityIndex). RegionIndex not found");
		return cityIt->second;
	}

	std::set<Map::CityIndex> Map::regionCities(RegionIndex index) const
	{
		auto regionIt = regionMap.find(index);
		if (regionIt == regionMap.end())
			throw std::exception("ERROR pan::Map::std::set<CityIndex>& Map::regionCities(RegionIndex). Invalid index");
		std::set<CityIndex> s;
		for (const auto& pair : cityRegionMap){
			if (pair.second == index)
				s.insert(pair.first);
		}
		return s;
	}

	/**	Private interface*/
	bool Map::addCityToRegion(CityIndex cIndex, RegionIndex rIndex)
	{
		// Validate cityIndex
		if (!(cIndex >= 0 && cIndex < numCities()))
			return false;
		// Validate regionindex
		auto region = regionMap.find(rIndex);
		// Invalid region
		if (region == regionMap.end())
			return false;
		// Check if city is in the region
		auto city = cityRegionMap.find(cIndex);
		// City yet unassigned
		if (city == cityRegionMap.end())
			cityRegionMap.insert(std::make_pair(cIndex, rIndex));
		else 
			city->second = rIndex;
		return true;
	}

	RegionIndex Map::addRegion(const Region& r)
	{
		RegionIndex lastKey = regionMap.rbegin()->first;
		RegionIndex newKey = lastKey + 1;
		auto result = regionMap.insert(std::make_pair(newKey, r));
#ifdef _DEBUG
		// The insertion did not take place for unknown reason.
		assert(result.second && "ERROR pan::Map::addRegion. Region overwritten");
#endif
		return newKey;
	}

	bool Map::removeRegion(RegionIndex index)
	{
		auto region = regionMap.find(index);
		if (region == regionMap.end())
			return false;
		// The map is invalid state. Attempting to delete the only region.
		if (regionMap.size() == 1)
			throw std::exception("ERROR pan::Map::bool Map::removeRegion(RegionIndex). Attemprting to remove the only region");
		regionMap.erase(region);
		return true;
	}

	Map Map::pandemicMap()
	{
		Map m;
		City atlanta("Atlanta");
		atlanta.researchStation = true;
		auto iAtlanta = m.addCity(atlanta);
		City chicago("Chicago");
		auto iChicago = m.addCity(chicago);
		m.addConnection(iAtlanta, iChicago);
		City washington("Washington");
		auto iWashington = m.addCity(washington);
		m.addConnection(iAtlanta, iWashington);
		City miami("Miami");
		auto iMiami = m.addCity(miami);
		m.addConnection(iAtlanta, iMiami);
		City montreal("Montreal");
		auto iMontreal = m.addCity(montreal);
		m.addConnection(iMontreal, iChicago);
		m.addConnection(iMontreal, iWashington);
		City newyork("New-York");
		auto iNewYork = m.addCity(newyork);
		m.addConnection(iNewYork, iMontreal);
		m.addConnection(iNewYork, iWashington);
		return m;
	}
}
