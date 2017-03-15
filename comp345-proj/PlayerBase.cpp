#include "stdafx.h"
#include "PlayerBase.h"
#include "ReferenceCard.h"


namespace pan{
	PlayerBase::PlayerBase(const RoleBase& role) :
	role(role)
	{
	}

	PlayerBase::PlayerBase(const RoleBase& role,const std::string& name) :
	role(role),
    name(name)
	{
	}

	PlayerBase::~PlayerBase()
	{
	}

	bool PlayerBase::operator==(const PlayerBase& o) const
	{
		bool equals = (this->location == o.location && this->name == o.name && this->role == o.role
			&& this->cards.size() == o.cards.size());
		if (!equals)
			return false;
		for (std::size_t i = 0; i < cards.size(); i++){
			if (*cards._Get_container()[i] != *o.cards._Get_container()[i])
				return false;
		}
		return true;
	}

	std::string PlayerBase::description() const
	{
		std::string result = "Player: " + name + "\nRole: " + role.description() +
			"\nLocation: " + std::to_string(this->location) + "\nCards:\n";
		for (const auto& c : cards._Get_container()){
			result += c->description() + '\n';
		}
		return result;
	}
}