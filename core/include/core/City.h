#pragma once


namespace pan{
	/** @brief Represents a single city on the map.
	*	Is default constructible, copyable and assignable to allow usage with containers.
	*	@author Hrachya Hakobyan
	*/
	class City {
	public:
		City();
		City(const std::string& name, unsigned int population = 0);
		City(const std::string& name, unsigned int population, double xpos, double ypos);
		City(const City&);
		City(City&& o);
		City& operator=(const City&);
		City& operator=(City&&);
		~City() = default;

		bool operator==(const City& other) const;
		inline bool operator!=(const City& other) const;

		unsigned int population = 0;
		bool researchStation = false;

		std::string description() const;
		inline std::size_t playerCount() const;
		inline const std::set<PlayerIndex>& getPlayers() const;
		inline bool containsPlayer(PlayerIndex p) const;
		inline void addPlayer(PlayerIndex p);
		inline void removePlayer(PlayerIndex p);
		inline const std::string& getName() const;
		inline void setName(const std::string& name);
		inline RegionIndex getRegion() const;
		inline void setRegion(RegionIndex region);
		inline double getXpos() const { return xpos; }
		inline double getYpos() const { return ypos; }
		void setXpos(double x) { xpos = x; }
		void setYpos(double y) { ypos = y; }
		std::size_t getCubes(DiseaseType r) const;
		void setCubes(DiseaseType r, std::size_t cubes);

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_NVP(name);
			ar & BOOST_SERIALIZATION_NVP(population);
			ar & BOOST_SERIALIZATION_NVP(researchStation);
			ar & BOOST_SERIALIZATION_NVP(players);
			ar & BOOST_SERIALIZATION_NVP(cubes);
			ar & BOOST_SERIALIZATION_NVP(xpos);
			ar & BOOST_SERIALIZATION_NVP(ypos);
			ar & BOOST_SERIALIZATION_NVP(region);
		}
	private:
		std::set<PlayerIndex> players;
		std::string name;
		std::vector<std::size_t> cubes;
		double xpos;
		double ypos;
		RegionIndex region;
	};

	bool City::operator!=(const City& other) const
	{
		return !((*this) == other);
	}

	std::size_t City::playerCount() const
	{
		return players.size();
	}

	const std::set<PlayerIndex>& City::getPlayers() const
	{
		return players;
	}

	bool City::containsPlayer(PlayerIndex p) const
	{
		return (players.find(p) != players.end());
	}

	void City::addPlayer(PlayerIndex p)
	{
		players.insert(p);
	}

	void City::removePlayer(PlayerIndex p)
	{
		players.erase(p);
	}

	const std::string& City::getName() const
	{
		return name;
	}

	void City::setName(const std::string& name)
	{
		this->name = name;
	}

	RegionIndex City::getRegion() const
	{
		return region;
	}

	void City::setRegion(RegionIndex region)
	{
		this->region = region;
	}
}

