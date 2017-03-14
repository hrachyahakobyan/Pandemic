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
		for (std::size_t i = 0; i < numCities(); i++){
			res += this->operator[](i).description() + '\n';
		}
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
		auto iAtlanta = m.addCity(regionBlue, City("Atlanta", 447841));
		auto iChicago = m.addCity(regionBlue, City("Chicago", 2719000));
		auto iEssen = m.addCity(regionBlue, City("Essen", 566862));
		auto iLondon = m.addCity(regionBlue, City("London", 8674000));
		auto iMadrid = m.addCity(regionBlue, City("Madrid", 3165000));
		auto iMilan = m.addCity(regionBlue, City("Milan", 1251000));
		auto iMontreal = m.addCity(regionBlue, City("Montreal", 1650000));
		auto iNewYork = m.addCity(regionBlue, City("NewYork", 8406000));
		auto iParis = m.addCity(regionBlue, City("Paris", 2244000));
		auto iSanFrancisco = m.addCity(regionBlue, City("SanFrancisco", 837442));
		auto iStPetersburg = m.addCity(regionBlue, City("StPetersburg", 4991000));
		auto iWashington = m.addCity(regionBlue, City("Washington", 7062000));

		auto iAlgiers = m.addCity(regionBlack, City("Algiers", 3416000));
		auto iBaghdad = m.addCity(regionBlack, City("Baghdad", 7665000));
		auto iCairo = m.addCity(regionBlack, City("Cairo", 9120000));
		auto iChennai = m.addCity(regionBlack, City("Chennai", 7088000));
		auto iDelhi = m.addCity(regionBlack, City("Delhi", 18980000));
		auto iIstanbul = m.addCity(regionBlack, City("Istanbul", 14800000));
		auto iKarachi = m.addCity(regionBlack, City("Karachi", 25300000));
		auto iKolkata = m.addCity(regionBlack, City("Kolkata", 4497000));
		auto iMoscow = m.addCity(regionBlack, City("Moscow", 11920000));
		auto iMumbai = m.addCity(regionBlack, City("Mumbai", 18410000));
		auto iRiyadh = m.addCity(regionBlack, City("Riyadh", 8000000));
		auto iTehran = m.addCity(regionBlack, City("Tehran", 8154000));

		auto iBogota = m.addCity(regionYellow, City("Bogota", 8081000));
		auto iBuenosAries = m.addCity(regionYellow, City("BuenosAries", 2891000));
		auto iJohannesburg = m.addCity(regionYellow, City("Johannesburg", 4435000));
		auto iKhartoum = m.addCity(regionYellow, City("Khartoum", 5185000));
		auto iKinshasa = m.addCity(regionYellow, City("Kinshasa", 10120000));
		auto iLagos = m.addCity(regionYellow, City("Lagos", 21000000));
		auto iLima = m.addCity(regionYellow, City("Lima", 8473000));
		auto iLosAngeles = m.addCity(regionYellow, City("LosAngeles", 3884000));
		auto iMexicoCity = m.addCity(regionYellow, City("MexicoCity", 8851000));
		auto iMiami = m.addCity(regionYellow, City("Miami", 417650));
		auto iSantiago = m.addCity(regionYellow, City("Santiago", 5128000));
		auto iSaoPaulo = m.addCity(regionYellow, City("SaoPaulo", 12040000));

		auto iBangkok = m.addCity(regionRed, City("Bangkok", 8281000));
		auto iBeijing = m.addCity(regionRed, City("Beijing", 21500000));
		auto iHoChiMinhCity = m.addCity(regionRed, City("HoChiMinhCity", 8426000));
		auto iHongKong = m.addCity(regionRed, City("HongKong", 7188000));
		auto iJakarta = m.addCity(regionRed, City("Jakarta", 9608000));
		auto iManila = m.addCity(regionRed, City("Manila", 1652000));
		auto iOsaka = m.addCity(regionRed, City("Osaka", 2665000));
		auto iSeoul = m.addCity(regionRed, City("Seoul", 10010000));
		auto iShanghai = m.addCity(regionRed, City("Shanghai", 24150000));
		auto iSydney = m.addCity(regionRed, City("Sydney", 4293000));
		auto iTaipei = m.addCity(regionRed, City("Taipei", 2705000));
		auto iTokyo = m.addCity(regionRed, City("Tokyo", 13620000));

		// Connect cities.
		m.addConnection(iAtlanta, iChicago);
		m.addConnection(iAtlanta, iWashington);
		m.addConnection(iAtlanta, iMiami);
		m.addConnection(iChicago, iMontreal);
		m.addConnection(iChicago, iSanFrancisco);
		m.addConnection(iChicago, iLosAngeles);
		m.addConnection(iMontreal, iNewYork);
		m.addConnection(iMontreal, iWashington);
		m.addConnection(iSanFrancisco, iLosAngeles);
		m.addConnection(iMexicoCity, iMiami);
		m.addConnection(iMexicoCity, iBogota);
		m.addConnection(iMexicoCity, iLima);
		m.addConnection(iMexicoCity, iLosAngeles);
		m.addConnection(iWashington, iNewYork);
		m.addConnection(iWashington, iMiami);
		m.addConnection(iLima, iBogota);
		m.addConnection(iLima, iSantiago);
		m.addConnection(iBogota, iBuenosAries);
		m.addConnection(iBogota, iSaoPaulo);
		m.addConnection(iBogota, iMiami);
		m.addConnection(iBuenosAries, iSaoPaulo);
		m.addConnection(iSaoPaulo, iLagos);
		m.addConnection(iSaoPaulo, iMadrid);
		m.addConnection(iLagos, iKinshasa);
		m.addConnection(iLagos, iKhartoum);
		m.addConnection(iKinshasa, iKhartoum);
		m.addConnection(iKinshasa, iJohannesburg);
		m.addConnection(iJohannesburg, iKhartoum);
		m.addConnection(iKhartoum, iCairo);
		m.addConnection(iCairo, iAlgiers);
		m.addConnection(iCairo, iRiyadh);
		m.addConnection(iCairo, iIstanbul);
		m.addConnection(iCairo, iBaghdad);
		m.addConnection(iAlgiers, iIstanbul);
		m.addConnection(iAlgiers, iMadrid);
		m.addConnection(iAlgiers, iParis);
		m.addConnection(iMadrid, iLondon);
		m.addConnection(iMadrid, iNewYork);
		m.addConnection(iMadrid, iParis);
		m.addConnection(iLondon, iEssen);
		m.addConnection(iLondon, iParis);
		m.addConnection(iParis, iMilan);
		m.addConnection(iParis, iEssen);
		m.addConnection(iEssen, iStPetersburg);
		m.addConnection(iEssen, iMilan);
		m.addConnection(iMilan, iIstanbul);
		m.addConnection(iIstanbul, iStPetersburg);
		m.addConnection(iIstanbul, iBaghdad);
		m.addConnection(iBaghdad, iRiyadh);
		m.addConnection(iBaghdad, iKarachi);
		m.addConnection(iBaghdad, iTehran);
		m.addConnection(iKarachi, iTehran);
		m.addConnection(iKarachi, iRiyadh);
		m.addConnection(iKarachi, iDelhi);
		m.addConnection(iKarachi, iMumbai);
		m.addConnection(iDelhi, iKolkata);
		m.addConnection(iDelhi, iMumbai);
		m.addConnection(iDelhi, iChennai);
		m.addConnection(iDelhi, iTehran);
		m.addConnection(iTehran, iMoscow);
		m.addConnection(iMoscow, iIstanbul);
		m.addConnection(iMoscow, iStPetersburg);
		m.addConnection(iMumbai, iChennai);
		m.addConnection(iChennai, iKolkata);
		m.addConnection(iChennai, iBangkok);
		m.addConnection(iChennai, iJakarta);
		m.addConnection(iKolkata, iHongKong);
		m.addConnection(iKolkata, iBangkok);
		m.addConnection(iBangkok, iHoChiMinhCity);
		m.addConnection(iBangkok, iJakarta);
		m.addConnection(iBangkok, iHongKong);
		m.addConnection(iHoChiMinhCity, iJakarta);
		m.addConnection(iHoChiMinhCity, iHongKong);
		m.addConnection(iHoChiMinhCity, iManila);
		m.addConnection(iHongKong, iManila);
		m.addConnection(iHongKong, iTaipei);
		m.addConnection(iHongKong, iShanghai);
		m.addConnection(iTaipei, iOsaka);
		m.addConnection(iTaipei, iManila);
		m.addConnection(iTaipei, iShanghai);
		m.addConnection(iShanghai, iBeijing);
		m.addConnection(iShanghai, iSeoul);
		m.addConnection(iShanghai, iTokyo);
		m.addConnection(iBeijing, iSeoul);
		m.addConnection(iSeoul, iTokyo);
		m.addConnection(iTokyo, iOsaka);
		m.addConnection(iTokyo, iSanFrancisco);
		m.addConnection(iManila, iSydney);
		m.addConnection(iManila, iSanFrancisco);
		m.addConnection(iSydney, iJakarta);
		m.addConnection(iSydney, iLosAngeles);

		return m;
	}
}
