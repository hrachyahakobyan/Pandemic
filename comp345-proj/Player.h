#pragma once
#include "PlayerBase.h"

namespace pan{
	/**
	*	@brief Initial mockup of Player class.
	*	The Player class accepts a template parameter which must be 
	*	a subclass of Role. Note, even though the template is generic
	*	, the type of the template is forced to be a subclass of Role
	*	by the pure virtual getter of PlayerBase.
	*	@author Hrachya Hakobyan
	*/
	template<typename R>
	class Player : public PlayerBase
	{
	public:
		Player();
		Player(const std::string& name);
		~Player();

		RoleIndex roleIndex() const;
		const Role& getRole() const;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PlayerBase);
			ar & BOOST_SERIALIZATION_NVP(role);
		}
	private:
		R role;
	};

	template<typename R>
	Player<R>::Player()
	{

	}

	template<typename R>
	Player<R>::Player(const std::string& name) :
		PlayerBase(name)
	{

	}

	template<typename R>
	Player<R>::~Player()
	{

	}

	template<typename R>
	const Role& Player<R>::getRole() const
	{
		return role;
	}

	template<typename R>
	RoleIndex Player<R>::roleIndex() const
	{
		return R::roleIndex;
	}
}

