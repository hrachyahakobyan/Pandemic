#include "stdafx.h"
#include "Map.h"
#include "FileManager.h"

namespace pan{
	Map Map::panMap;

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
		cityRegions(std::move(o.cityRegions))
	{
	}

	Map::Map(const Map& o) :
		graph(o.graph),
		regionMap(o.regionMap),
		cityRegions(o.cityRegions)
	{
	}

	Map& Map::operator=(const Map& o)
	{
		this->graph = o.graph;
		this->regionMap = o.regionMap;
		this->cityRegions = o.cityRegions;
		return *this;
	}

	Map& Map::operator=(Map&& o)
	{
		this->graph = std::move(o.graph);
		this->regionMap = std::move(o.regionMap);
		this->cityRegions = std::move(o.cityRegions);
		return *this;
	}

	bool Map::operator==(const Map& other) const
	{
		if (!(graph == other.graph && regionMap == other.regionMap 
			&& cityRegions == other.cityRegions && regionMap == other.regionMap))
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

	CityIndex Map::addCity(const City& city)
	{
		auto ci = graph.addVertex(city);
		bool addRegion = addCityToRegion(ci, regionMap.begin()->first);
#ifdef _DEBUG
		assert(addRegion && "ERROR pan::CityIndex addCity(const City&): Could not add city to region");
#endif
		return ci;
	}

	/**
	*	Adds a new city to the specified region.
	*	@throws std::exception if the region index is invalid
	*	@return the index of the newly created city
	*/
	CityIndex Map::addCity(RegionIndex region, const City& c)
	{
		auto regionIt = regionMap.find(region);
		if (regionIt == regionMap.end())
			throw std::exception("ERROR pan::CityIndex addCity(RegionIndex region, const City&). Invalid region");
		auto cityIndex = addCity(c);
		addCityToRegion(cityIndex, region);
		return cityIndex;
	}

	void Map::removeCity(CityIndex i)
	{
		if (graph.vertexExists(i)){
			cityRegions.erase(cityRegions.begin() + i);
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
		return cityRegions[i];
	}

	std::set<CityIndex> Map::regionCities(RegionIndex index) const
	{
		auto regionIt = regionMap.find(index);
		if (regionIt == regionMap.end())
			throw std::exception("ERROR pan::Map::std::set<CityIndex>& Map::regionCities(RegionIndex). Invalid index");
		std::set<CityIndex> s;
		for (CityIndex i = 0; i < cityRegions.size(); i++){
			if (cityRegions[i] == index){
				s.insert(i);
			}
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
		if (cIndex == cityRegions.size())
			cityRegions.push_back(rIndex);
		else 
			cityRegions[cIndex] = rIndex;
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
		static bool load;
		if (!load){
			FileManager::getInstance().load(panMap, "pandemic_map.xml", "resources");
		}
		load = true;
		return panMap;
		
		/*
		Map m;
		RegionIndex regionBlue = 0;
		RegionIndex regionYellow = m.addRegion();
		RegionIndex regionBlack = m.addRegion();
		RegionIndex regionRed = m.addRegion();

		// City name and population
		auto iAtlanta = m.addCity(regionBlue, City("Atlanta", 447841, 0.239, 0.435));
		auto iSanFrancisco = m.addCity(regionBlue, City("San Francisco", 837442, 0.144, 0.439));
		auto iChicago = m.addCity(regionBlue, City("Chicago", 2719000, 0.236, 0.376));
		auto iMontreal = m.addCity(regionBlue, City("Montreal", 1650000, 0.297, 0.375));
		auto iNewYork = m.addCity(regionBlue, City("New York", 8406000, 0.287, 0.410));
		auto iWashington = m.addCity(regionBlue, City("Washington", 658893, 0.273, 0.415));
		auto iLondon = m.addCity(regionBlue, City("London", 8674000, 0.474, 0.363));
		auto iMadrid = m.addCity(regionBlue, City("Madrid", 3615000, 0.467, 0.424));
		auto iParis = m.addCity(regionBlue, City("Paris", 2244000, 0.487, 0.375));
		auto iEssen = m.addCity(regionBlue, City("Essen", 566862, 0.499, 0.359));
		auto iMilan = m.addCity(regionBlue, City("Milan", 1251000, 0.502, 0.395));
		auto iStPetersburg = m.addCity(regionBlue, City("Saint-Petersburg", 4991000, 0.551, 0.304));

		auto iAlgiers = m.addCity(regionBlack, City("Algiers", 3416000, 0.488, 0.442));
		auto iBaghdad = m.addCity(regionBlack, City("Baghdad", 7665000, 0.602, 0.477));
		auto iCairo = m.addCity(regionBlack, City("Cairo", 9120000, 0.558, 0.475));
		auto iChennai = m.addCity(regionBlack, City("Chennai", 7088000, 0.706, 0.552));
		auto iDelhi = m.addCity(regionBlack, City("Delhi", 18980000, 0.701, 0.488));
		auto iIstanbul = m.addCity(regionBlack, City("Istanbul", 14800000, 0.557, 0.419));
		auto iKarachi = m.addCity(regionBlack, City("Karachi", 25300000, 0.671, 0.504));
		auto iKolkata = m.addCity(regionBlack, City("Kolkata", 4497000, 0.731, 0.513));
		auto iMoscow = m.addCity(regionBlack, City("Moscow", 11920000, 0.571, 0.328));
		auto iMumbai = m.addCity(regionBlack, City("Mumbai", 18410000, 0.691, 0.533));
		auto iRiyadh = m.addCity(regionBlack, City("Riyadh", 8000000, 0.607, 0.497));
		auto iTehran = m.addCity(regionBlack, City("Tehran", 8154000, 0.618, 0.442));

		auto iLosAngeles = m.addCity(regionYellow, City("Los Angeles", 3884000, 0.155, 0.450));
		auto iMexicoCity = m.addCity(regionYellow, City("Mexico City", 8851000, 0.196, 0.521));
		auto iMiami = m.addCity(regionYellow, City("Miami", 417650, 0.250, 0.494));
		auto iBogota = m.addCity(regionYellow, City("Bogota", 8081000, 0.275, 0.6));
		auto iLima = m.addCity(regionYellow, City("Lima", 8473000, 0.264, 0.675));
		auto iSantiago = m.addCity(regionYellow, City("Santiago", 5128000, 0.287, 0.769));
		auto iBuenosAries = m.addCity(regionYellow, City("Buenos Aires", 2891000, 0.324, 0.783));
		auto iSaoPaulo = m.addCity(regionYellow, City("Sao Pauolo", 12040000, 0.356, 0.724));
		auto iLagos = m.addCity(regionYellow, City("Lagos", 21000000, 0.484, 0.587));
		auto iKinshasa = m.addCity(regionYellow, City("Kinshasa", 10120000, 0.527, 0.635));
		auto iJohannesburg = m.addCity(regionYellow, City("Johannesburg", 4435000, 0.552, 0.745));
		auto iKhartoum = m.addCity(regionYellow, City("Khartoum", 5185000, 0.570, 0.545));

		auto iBangkok = m.addCity(regionRed, City("Bangkok", 8281000, 0.773, 0.556));
		auto iBeijing = m.addCity(regionRed, City("Beijing", 21500000, 0.792, 0.403));
		auto iHoChiMinhCity = m.addCity(regionRed, City("HoChiMinhCity", 8426000));
		auto iHongKong = m.addCity(regionRed, City("HongKong", 7188000, 0.800, 0.502));
		auto iJakarta = m.addCity(regionRed, City("Jakarta", 9608000, 0.792, 0.645));
		auto iManila = m.addCity(regionRed, City("Manila", 1652000, 0.824, 0.550));
		auto iOsaka = m.addCity(regionRed, City("Osaka", 2665000, 0.853, 0.434));
		auto iSeoul = m.addCity(regionRed, City("Seoul", 10010000, 0.829, 0.420));
		auto iShanghai = m.addCity(regionRed, City("Shanghai", 24150000, 0.818, 0.461));
		auto iSydney = m.addCity(regionRed, City("Sydney", 4293000, 0.907, 0.775));
		auto iTaipei = m.addCity(regionRed, City("Taipei", 2705000, 0.819, 0.495));
		auto iTokyo = m.addCity(regionRed, City("Tokyo", 13620000, 0.864, 0.427));

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

		auto b = FileManager::getInstance().save(m, "pandemic_map.xml", "resources", true);
	
		return m;*/
	}
}
