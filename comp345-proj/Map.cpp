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

	/**
	*	Adds a new city to the specified region.
	*	@throws std::exception if the region index is invalid
	*	@return the index of the newly created city
	*/
	Map::CityIndex Map::addCity(RegionIndex region, const City& c)
	{
		auto regionIt = regionMap.find(region);
		if (regionIt == regionMap.end())
			throw std::exception("ERROR pan::Map::CityIndex addCity(RegionIndex region, const City&). Invalid region");
		auto cityIndex = addCity(c);
		addCityToRegion(cityIndex, region);
		return cityIndex;
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
		RegionIndex regionBlue = 0;
		RegionIndex regionYellow = m.addRegion();
		RegionIndex regionBlack = m.addRegion();
		RegionIndex regionRed = m.addRegion();

		// City name and population
		auto iAtlanta = m.addCity(regionBlue, City("Atlanta", 123123));
		auto iChicago = m.addCity(regionBlue, City("Chicago", 123123));
		// Connect cities.
		m.addConnection(iAtlanta, iChicago);

		/*
		City washington("Washington");
		City miami("Miami");
		City montreal("Montreal");
		City newyork("New-York");
		City sf("San Francisco");
		City LA("Los Angeles");
		City mexico("Mexico");
		City bogota("Bogota");
		City lima("Lima");
		City sPaulo("San Paulo");
		City santiago("Santiago");
		City bAires("Buenos Aires");
		City london("London");
		City madird("Madrid");
		City paris("Paris");
		City essem("Essem");
		City milan("Milan");
		City stpeter("St. Petersburg");
		City istanbul("Istanbul");
		City algiers("Algiers");
		City cairo("Cairo");
		City moscow("Moscow");
		City riyadh("Riyadh");
		City baghdad("Baghdad");
		City karachi("Karachi");
		City tehran("Tehran");
		City delhi("Delhi");
		City mumbai("Mumbai");
		City chennai("Chennai");
		City koulkata("Koulkata");
		City bangkok("Bangkok");
		City jakarta("Jakarta");
		City hochi("Ho Chi Minh");
		City hk("Hong Kong");
		City shanghai("Shanghai");
		City beijing("Beijing");
		City taipei("Taipei");
		City seoul("Seoul");
		City tokyo("Tokyo");
		City osaka("Osaka");
		City manila("Manila");
		City sydney("Sydney");
		City lagos("Lagos");
		City khartolim("Khartolim");
		City kinshasa("Kinshasa");
		City jb("Johannesburg");

		auto iDelhi = m.addCity(delhi);
		auto iMumbai = m.addCity(mumbai);
		auto iChennai = m.addCity(chennai);
		auto iKoulkata = m.addCity(koulkata);
		auto iBangkok = m.addCity(bangkok);
		auto iJakarta = m.addCity(jakarta);
		auto iHochi = m.addCity(hochi);
		auto iHK = m.addCity(hk);
		auto iShanghai = m.addCity(shanghai);
		auto iAtlanta = m.addCity(atlanta);
		auto iChicago = m.addCity(chicago);
		auto iMiami = m.addCity(miami);
		auto iWashington = m.addCity(washington);
		auto iMontreal = m.addCity(montreal);
		auto iNewYork = m.addCity(newyork);
		auto iSF = m.addCity(sf);
		auto iLA = m.addCity(LA);
		auto iMexico = m.addCity(mexico);
		auto iBogota = m.addCity(bogota);
		auto iLima = m.addCity(lima);
		auto iSpaulo = m.addCity(sPaulo);
		auto iSantiago = m.addCity(santiago);
		auto iBAires = m.addCity(bAires);
		auto iLondon = m.addCity(london);
		auto iMadird = m.addCity(madird);
		auto iParis = m.addCity(paris);
		auto iEssem = m.addCity(essem);
		auto iMilan = m.addCity(milan);
		auto iStPeter = m.addCity(stpeter);
		auto iIstanbul = m.addCity(istanbul);
		auto iAlgiers = m.addCity(algiers);
		auto iCairo = m.addCity(cairo);
		auto iMoscow = m.addCity(moscow);
		auto iRiyadh = m.addCity(riyadh);
		auto iBaghdad = m.addCity(baghdad);
		auto iKarachi = m.addCity(karachi);
		auto iTehran = m.addCity(tehran);


		m.addConnection(iAtlanta, iWashington);
		m.addConnection(iAtlanta, iChicago);
		m.addConnection(iAtlanta, iMiami);
		m.addConnection(iMontreal, iChicago);
		m.addConnection(iMontreal, iWashington);
		m.addConnection(iNewYork, iMontreal);
		m.addConnection(iNewYork, iWashington);
		*/
		return m;
	}
}
