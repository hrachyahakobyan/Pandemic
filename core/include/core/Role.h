#pragma once
namespace pan{
	/**
	*	@brief describes different roles present in the game
	*/
	enum class Roles : unsigned int{Medic = 0, Dispatcher, Scientist, 
		Researcher, QSpecialist, OperationsExpert, CPlanner
	};
	static const std::map<Roles, const char*> RolesDescriptions{
		{ Roles::Dispatcher, "Dispatcher" },
		{ Roles::OperationsExpert, "Operations Expert" },
		{ Roles::Scientist, "Scientist" },
		{ Roles::Medic, "Medic" },
		{ Roles::QSpecialist, "Quarantine Specialist" },
		{ Roles::Researcher, "Researcher" },
		{ Roles::CPlanner, "Contingency Planner" }
	};

	/**
	*	@brief A class to represent the Role entity in the game.
	*	The RoleBase is a the same as the Role card in the real game.
	*	The RoleBase is a prent class to concrete Role classes.
	*	The RolBase is not abstract, however it cannot be instantiated 
	*	because of protected constructor.
	*	@author Hrachya Hakobyan
	*/
	class RoleBase 
	{
	public:
		virtual ~RoleBase();
		inline bool operator==(const RoleBase&) const;
		inline bool operator!=(const RoleBase&) const;
		const Roles role;
		virtual std::string description() const;
	protected:
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

	/**
	*	@brief RoleImpl is a templated class for concrete Role-s.
	*	Its template parameter is an Roles enum value.
	*/
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

	typedef RoleImpl<Roles::Dispatcher> DispatcherRole;
	typedef RoleImpl<Roles::OperationsExpert> OperationsExpertRole;
	typedef RoleImpl<Roles::Scientist> ScientistRole;
	typedef RoleImpl<Roles::Medic> MedicRole;
	typedef RoleImpl<Roles::QSpecialist> QSpecialistRole;
	typedef RoleImpl<Roles::Researcher> ResearcherRole;
	typedef RoleImpl<Roles::CPlanner> CPlannerRole;
}

