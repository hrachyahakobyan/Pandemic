#pragma once
#include "ActionBase.h"
#include "Map.h"

namespace pan{
	/**
	*	@brief Encapsulates the parameters of Infect call
	*	@author Hrachya Hakobyan
	*/
	class Infect : public ActionImpl<Infect, ActionBase>
	{
	public:
		Infect(Map::CityIndex city, DiseaseType diseaseType, std::size_t cubes);
		Map::CityIndex city;
		std::size_t cubes;
		DiseaseType diseaseType;
		std::set<Map::CityIndex> outbreakedCities;
		ActionBase* clone() const;
	};
}

