#pragma once
#include "PlayerBase.h"

namespace pan{

	std::shared_ptr<PlayerBase> player(Roles role, const std::string& name = "");
	/**
	*	@brief Concrete subclass of PlayerBase
	*	The Player class accepts a template parameter which must be 
	*	a Roles enum type.
	*	@author Hrachya Hakobyan
	*/
	template<Roles R>
	class Player : public PlayerBase
	{
	public:
		Player();
		Player(const std::string& name);
		~Player();

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar.template register_type<pan::PlayerBase>();
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PlayerBase);
		}
	};

	template<Roles R>
	Player<R>::Player() :
	PlayerBase(RoleImpl<R>())
	{
	}

	template<Roles R>
	Player<R>::Player(const std::string& name) :
	PlayerBase(RoleImpl<R>(), name)
	{
	}

	template<Roles R>
	Player<R>::~Player()
	{
	}

	typedef Player<Roles::Dispatcher> Dispatcher;
	typedef Player<Roles::FOperative> FOperative;
	typedef Player<Roles::Generalist> Generalist;
	typedef Player<Roles::Medic> Medic;
	typedef Player<Roles::QSpecialist> QSpecialist;
	typedef Player<Roles::Researcher> Researcher;
	typedef Player<Roles::CPlanner> CPlanner;
}

