#pragma once
#include "Object.h"
#include "common.h"

namespace pan{
	/**
	*	@brief A class to represent the Role entity in the game.
	*	The Role is a the same as the Role card in the real game.
	*	The role does not inherit from Player. Is-a relationship
	*	between a player and a role is not correct.
	*	A role is in abstract parent to concrete Roles.
	*	@author Hrachya Hakobyan
	*/

	class Role : public Object
	{
	public:
		Role();
		virtual ~Role();
	};

	class Medic : public Role{
	public:
		static const RoleIndex roleIndex = 0;
		inline std::string description() const;
	};

	std::string Medic::description() const
	{
		return "Medic";
	}

	class Dispatcher : public Role{
	public:
		static const RoleIndex roleIndex = 1;
		inline std::string description() const;
	};

	std::string Dispatcher::description() const
	{
		return "Dispatcher";
	}
}

