#pragma once
#include "City.h"
#include "Region.h"

#include "detail\Graph.h"

namespace pan{
	/**
	*	@brief A class representing the game Map, i.e. the board.
	*	Note, by the rules of the game the Map requries at least one Region.
	*	If one is not given, a default one will be constructed.
	*	The regions are implemented as a mapping between CityIndex-s and
	*	RegionIndex-s and RegionIndex-s and Region objects.
	*	@author Hrachya Hakobyan
	*/
	class Map 
	{
	public:
		typedef detail::Graph<City>::VertexIterator CityIndexIterator;
		typedef detail::Graph<City>::VertexRange CityIndexRange;
		typedef detail::Graph<City>::AdjacencyIterator ConnectedCityIterator;
		typedef detail::Graph<City>::AdjacencyRange ConnectedCityRange;
		typedef detail::Graph<City>::EdgeIterator ConnectionIterator;
		typedef detail::Graph<City>::EdgeRange ConnectionRange;

		/**
		*	@brief default constructor for Map.
		*	Will create an initial region with index 0.
		*/
		Map();
		explicit Map(const Region& r);
		Map(const Map&);
		Map(Map&&);
		Map& operator=(const Map&);
		Map& operator=(Map&&);
		~Map() = default;

		static Map pandemicMap();

		/**
		*	Comparison operators.
		*	Note, full fledged comparison is not feasible (i.e. graph isomorphism).
		*	The comparison does not take into account edge connectivity of the cities.
		*/
		bool operator==(const Map& other) const;
		inline bool operator!=(const Map& other) const;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar.template register_type<pan::detail::Graph<pan::City>>();
			ar & BOOST_SERIALIZATION_NVP(graph);
			ar & BOOST_SERIALIZATION_NVP(regionMap);
		}

		/*!	Public Interaface */
		std::string description() const;

		/**
		*	Getter for the number of cities.
		*	@return the number of cities on the map
		*/
		inline std::size_t numCities() const;
		/**
		*	Getter for the number of connections.
		*	@return the number of connections, i.e. edges on the map.
		*/
		inline std::size_t numConnections() const;

		/**
		*	Checks if a city exists.
		*	@param index the CityIndex to be checked
		*	@return true if the city exists, false otherwise
		*/
		inline bool cityExists(CityIndex i) const;

		/**
		*	Returns the const reference of the City object at the corresponding index.
		*	@param i the CityIndex of the reference of the object to be returned
		*	@throws std::exception if the index in invalid
		*	@return	the constant reference of the City object at the specified index
		*/
		inline const City& operator[](CityIndex i) const;
		/**
		*	Returns the reference of the City object at the corresponding index.
		*	@param i the CityIndex of the reference of the object to be returned
		*	@throws std::exception if the index is invalid
		*	@return	the reference of the City object at the specified index
		*/
		inline City& operator[](CityIndex i);

		/**
		*	Iterate all ciites.
		*	@return a pair of city iterators
		*/
		inline CityIndexRange cities() const;

		/**
		*	Iterate all connections
		*	@return a pair of connection iterators
		*/
		inline ConnectionRange connections() const;

		inline CityIndex source(ConnectionIterator) const;
		inline CityIndex target(ConnectionIterator) const;

		/**
		*	Checks if cities at specified indeces are connected/
		*	@param i the index of the first City
		*	@param j the index of the second City
		*	@return true if a connection between the cities exists, false otherwise
		*/
		inline bool connectionExists(CityIndex i, CityIndex j) const;

		/**
		*	Returns the connected cities.
		*	@param i the city index
		*	@throws std::exception if index is invalid
		*	@return iterator pair for the neighbor cities of i
		*/
		inline ConnectedCityRange connectedCities(CityIndex i) const;

		/**
		*	Returns the number of regions in the map.
		*	@return the number of regions on the map
		*/
		inline std::size_t numRegions() const;

		/**
		*	Returns all regions in the map.
		*	@return vector of all regions in the map.
		*/
		std::vector<RegionIndex> getRegions() const;

		/**
		*	Returns the region with the specified index.
		*	@param index the index of the Region
		*	@throws std::exception if the index is invalid
		*	@return the const reference to the specified Region
		*/
		inline const Region& regionAt(RegionIndex index) const;

		/**
		*	Returns the CityIndex-s of the specified Region
		*	Caution, O(N) operation on the number of vertices.
		*	@param index the index of the region
		*	@throws std::exception if the index is invalid
		*	@return the set of CityIndex-s of the region
		*/
		 std::set<CityIndex> citiesOfRegion(RegionIndex index) const;
		
	private:
		static Map panMap;

#ifdef _DEBUG
#ifndef DISABLE_TESTS
		FRIEND_TESTS
#endif
#endif

		typedef detail::Graph<City> Graph;
		typedef detail::Graph<City>::EdgeDescriptor ConnectionDescriptor;

		Graph graph;
		std::map<RegionIndex, Region> regionMap;

		/*!	Private interface */
		/**
		*	Adds a new City. The city will be assigned to the first Region in the map.
		*	@param c the City object to add. Defaults to City()
		*	@return the CityIndex of the added city
		*/
		CityIndex addCity(const City& c = City());

		/**
		*	Adds a new city to the specified region.
		*	If the region is invalid, the city will not be added.
		*	@throws std::exception if the region index is invalid
		*	@return the index of the newly created city
		*/
		CityIndex addCity(RegionIndex region, const City& c = City());

		/**
		*	Removes a city.
		*	CAUTION.
		*	Invalidates all other CityIndeces, ConnectionDescriptors
		*	Use with extreme caution. The invalidations
		*	are not handled.
		*	@param i the index of the city to be removed
		*/
		 void removeCity(CityIndex i);

		/**
		*	Adds a connection between two cities
		*	@param v1 the index of first city
		*	@param v2 the index of the second city
		*	@return if the operation is successful, the second item will be true
		*	and the first item will be the newly added edge descriptor.
		*	Otherwise, the second parameter will be false.
		*	The operation is successful if no connection previously existed 
		*	and both indeces are valid.
		*/
		inline std::pair<ConnectionDescriptor, bool> addConnection(CityIndex v1, CityIndex v2);

		/**
		*	Removes a connection between two cities.
		*	@param v1 the index of the first city
		*	@param v2 the index of the second city
		*/
		inline void removeConnection(CityIndex v1, CityIndex v2);

		/**
		*	Returns the non-const reference to the Region.
		*	@param index the index of the Region
		*	@throws std::exception if the index is invalid
		*	@return the reference to Region
		*/
		inline Region& regionAt(RegionIndex index);

		/**
		*	Adds a new Region to the map.
		*	@param r the region to be added. Defaults to Region()
		*	@return RegionIndex the index of the added region
		*/
		RegionIndex addRegion(const Region& r = Region());

		/**
		*	Removes a Region with the specified index.
		*	CAUTION. Might set the Map into an invalid state having City-s with
		*	invalid RegionIndex-s.
		*	@param index the index of the region to be removed
		*	@throws std::exception if the index is invalid, or if the index is the only reamining region
		*	@return true if the region existed and was removed successfuly, false otherwise
		*/
		bool removeRegion(RegionIndex index);

		/**
		*	Adds the specified city to the specified region
		*	@param cIndex the index of the city to be added to region
		*	@param rIndex the index of the region 
		*	@return true if the operation is successul, false otherwise
		*	The operation is successful if the indeces are valid.
		*/
		bool addCityToRegion(CityIndex cIndex, RegionIndex rIndex);
	};

	bool Map::operator!=(const Map& other) const
	{
		return !(this->operator==(other));
	}

	/** Public Interface	*/
	std::size_t Map::numCities() const
	{
		return graph.numVertices();
	}

	std::size_t Map::numConnections() const
	{
		return graph.numEdges();
	}

	bool Map::cityExists(CityIndex i) const
	{
		return graph.vertexExists(i);
	}

	const City& Map::operator[](CityIndex i) const
	{
		return graph[i];
	}

	City& Map::operator[](CityIndex i)
	{
		return graph[i];
	}

	Map::CityIndexRange Map::cities() const
	{
		return graph.vertices();
	}

	Map::ConnectionRange Map::connections() const
	{
		return graph.edges();
	}

	CityIndex Map::source(ConnectionIterator e) const
	{
		return graph.source(e);
	}

	CityIndex Map::target(ConnectionIterator e) const
	{
		return graph.target(e);
	}

	bool Map::connectionExists(CityIndex i, CityIndex j) const
	{
		return graph.edgeExists(i, j);
	}

	Map::ConnectedCityRange Map::connectedCities(CityIndex i) const
	{
		return graph.neighbors(i);
	}

	std::size_t Map::numRegions() const
	{
		return regionMap.size();
	}

	const Region& Map::regionAt(RegionIndex index) const
	{
		auto regionIt = regionMap.find(index);
		if (regionIt == regionMap.end())
			throw std::exception("ERROR pan::Map::const Region& region(RegionIndex). Invalid index");
		return regionIt->second;
	}

	std::pair<Map::ConnectionDescriptor, bool> Map::addConnection(CityIndex v1, CityIndex v2)
	{
		return graph.addEdge(v1, v2);
	}

	void Map::removeConnection(CityIndex v1, CityIndex v2)
	{
		graph.removeEdge(v1, v2);
	}

	Region& Map::regionAt(RegionIndex index)
	{
		return const_cast<Region&>(static_cast<const Map*>(this)->regionAt(index));
	}
}

