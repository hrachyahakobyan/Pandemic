#include "stdafx.h"
#include "Role.h"

namespace pan{
	RoleBase::RoleBase(Roles role) :
	role(role)
	{
	}

	RoleBase::~RoleBase()
	{
	}

	std::string RoleBase::description() const
	{
		return RolesDescriptions.at(role);
	}
}
