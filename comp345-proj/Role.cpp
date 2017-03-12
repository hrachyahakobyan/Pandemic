#include "stdafx.h"
#include "Role.h"

namespace pan{
	RoleBase::RoleBase() :
	role(Roles::Medic)
	{
	}

	RoleBase::RoleBase(Roles role) :
	role(role)
	{
	}
}
