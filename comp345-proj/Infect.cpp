#include "stdafx.h"
#include "Infect.h"

namespace pan{
	Infect::Infect(CityIndex c, DiseaseType diseaseType, std::size_t cubes)
		: city(c), cubes(cubes), diseaseType(diseaseType)
	{
	}
}