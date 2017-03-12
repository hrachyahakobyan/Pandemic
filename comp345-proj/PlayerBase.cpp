#include "stdafx.h"
#include "PlayerBase.h"
#include "ReferenceCard.h"


namespace pan{
	PlayerBase::PlayerBase() :
	referenceCard(ReferenceCard::getInstance())
	{
	}

	PlayerBase::PlayerBase(const RoleBase& role) :
		role(role),
		referenceCard(ReferenceCard::getInstance())
	{
	}

	PlayerBase::PlayerBase(const RoleBase& role,const std::string& name) :
		role(role),
		referenceCard(ReferenceCard::getInstance()), name(name)
	{
	}

	PlayerBase::~PlayerBase()
	{

	}

	std::string PlayerBase::description() const
	{
		return "Player " + name + ". Role: " + role.description() +
			"\n. Location: " + std::to_string(this->location);
	}
}