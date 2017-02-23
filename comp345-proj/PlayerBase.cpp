#include "stdafx.h"
#include "PlayerBase.h"
#include "ReferenceCard.h"


namespace pan{
	PlayerBase::PlayerBase() :
		referenceCard(ReferenceCard::getInstance())
	{

	}

	PlayerBase::PlayerBase(const std::string& name) :
		referenceCard(ReferenceCard::getInstance()), name(name)
	{

	}

	PlayerBase::~PlayerBase()
	{

	}

	std::string PlayerBase::description() const
	{
		return "Player " + name + ". Role: " + this->getRole().description() +
			"\n. Location: " + std::to_string(this->location);
	}
}