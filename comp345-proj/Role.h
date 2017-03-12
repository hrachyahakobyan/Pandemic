#pragma once
#include "Object.h"
#include "common.h"

namespace pan{
	enum class Roles : unsigned int{Medic = 0, Dispatcher, Generalist, 
									Researcher, QSpecialist, FOperative};
	static std::map<Roles, const char*> RolesDescriptions{
		{ Roles::Dispatcher, "Dispatcher" },
		{ Roles::FOperative, "Field Operative" },
		{ Roles::Generalist, "Generalist" },
		{ Roles::Medic, "Medic" },
		{ Roles::QSpecialist, "Quarantine Specialist" },
		{ Roles::Researcher, "Researcher" }
	};

	/**
	*	@brief A class to represent the Role entity in the game.
	*	The Role is a the same as the Role card in the real game.
	*	The role does not inherit from Player. Is-a relationship
	*	between a player and a role is not correct.
	*	A role is in abstract parent to concrete Roles.
	*	@author Hrachya Hakobyan
	*/
	class RoleBase : public Object
	{
	public:
		virtual ~RoleBase();
		inline bool operator==(const RoleBase&) const;
		inline bool operator!=(const RoleBase&) const;
		const Roles role;
		inline std::string description() const;
	protected:
		RoleBase();
		RoleBase(Roles role);
	};

	bool RoleBase::operator==(const RoleBase& r) const
	{
		return this->role == r.role;
	}

	bool RoleBase::operator!=(const RoleBase& r) const
	{
		return this->role != r.role;
	}

	std::string RoleBase::description() const
	{
		return RolesDescriptions[role];
	}

	template<Roles R>
	class RoleImpl : public RoleBase
	{
	public:
		RoleImpl();
	};

	template<Roles R>
	RoleImpl<R>::RoleImpl() :
	RoleBase(R)
	{
	}

	typedef RoleImpl<Roles::Dispatcher> Dispatcher;
	typedef RoleImpl<Roles::FOperative> FOperative;
	typedef RoleImpl<Roles::Generalist> Generalist;
	typedef RoleImpl<Roles::Medic> Medic;
	typedef RoleImpl<Roles::QSpecialist> QSpecialist;
	typedef RoleImpl<Roles::Researcher> Researcher;
}

