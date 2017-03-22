#include "stdafx.h"
#include "Disease.h"

namespace pan{
	Disease::Disease(DiseaseType t) :
		diseaseType(t),
		isCured(false),
		isEradicated(false)
	{
	}

	Disease::Disease(const Disease& o):
		diseaseType(o.diseaseType),
		isCured(o.isCured),
		isEradicated(o.isEradicated)
	{

	}

	Disease& Disease::operator=(const Disease& o)
	{
		this->diseaseType = o.diseaseType;
		this->isCured = o.isCured;
		this->isEradicated = o.isEradicated;
		return *this;
	}

	void Disease::setIsCured(bool isCured)
	{
		// Keep it consistent.
		this->isCured = isCured;
		if (!isCured)
			this->isEradicated = false;
	}

	void Disease::setIsEradicated(bool isEradicated)
	{
		// If is cured, allow eradication
		if (isEradicated && this->isCured)
			this->isEradicated = true;
		// Revert back to not being eradicated
		else if (!isEradicated)
			this->isEradicated = false;
	}

	std::string Disease::description() const
	{
		return "Disease type: " + std::to_string(diseaseType) +
			". Is Cured: " + std::to_string(isCured) + ". Is eradicated: " + std::to_string(isEradicated);
	}
}