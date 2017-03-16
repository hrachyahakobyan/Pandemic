#pragma once
#include "ActionBase.h"

namespace pan{
	/**
	*	@brief Encapsulates the parameters of Infect call
	*	@author Hrachya Hakobyan
	*/
	class Infect : public ActionImpl<Infect, ActionBase>
	{
	public:
		Infect(CityIndex city, DiseaseType diseaseType, std::size_t cubes);
		/**
		*	The city to infect
		*/
		CityIndex city;
		/**
		*	How many cubes to put
		*/
		std::size_t cubes;
		/**
		*	The disease type of the cubes
		*/
		DiseaseType diseaseType;
		/**
		*	Stores the cities which suffered an outbreaked caused by this infection.
		*/
		std::set<CityIndex> outbreakedCities;
	};
}

