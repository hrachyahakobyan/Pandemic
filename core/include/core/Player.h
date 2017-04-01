#pragma once
#include "PlayerBase.h"

namespace pan{

	std::shared_ptr<PlayerBase> player(Roles role, PlayerIndex index, const std::string& name = "");
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
		Player(PlayerIndex index);
		Player(PlayerIndex index, const std::string& name);
		~Player();
		friend class boost::serialization::access;
		const RoleBase& getRole() const;
		const RoleImpl<R> role;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar.template register_type<pan::PlayerBase>();
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PlayerBase);
		}
	};

	template<Roles R>
	const pan::RoleBase& Player<R>::getRole() const
	{
		return role;
	}

	template<Roles R>
	Player<R>::Player(PlayerIndex index) :
	PlayerBase(index)
	{
	}

	template<Roles R>
	Player<R>::Player(PlayerIndex index, const std::string& name) :
	PlayerBase(index, name)
	{
	}

	template<Roles R>
	Player<R>::~Player()
	{
	}

	typedef Player<Roles::Dispatcher> Dispatcher;
	typedef Player<Roles::OperationsExpert> OperationsExpert;
	typedef Player<Roles::Scientist> Scientist;
	typedef Player<Roles::Medic> Medic;
	typedef Player<Roles::QSpecialist> QSpecialist;
	typedef Player<Roles::Researcher> Researcher;
	typedef Player<Roles::CPlanner> CPlanner;
}

BOOST_CLASS_EXPORT_KEY(pan::PlayerBase);
BOOST_CLASS_EXPORT_KEY(pan::Player<pan::Roles::Dispatcher>);
BOOST_CLASS_EXPORT_KEY(pan::Player<pan::Roles::OperationsExpert>);
BOOST_CLASS_EXPORT_KEY(pan::Player<pan::Roles::Scientist>);
BOOST_CLASS_EXPORT_KEY(pan::Player<pan::Roles::Medic>);
BOOST_CLASS_EXPORT_KEY(pan::Player<pan::Roles::QSpecialist>);
BOOST_CLASS_EXPORT_KEY(pan::Player<pan::Roles::Researcher>);
BOOST_CLASS_EXPORT_KEY(pan::Player<pan::Roles::CPlanner>);


#define BOOST_PTR_SERIALIZE(PlayerType) \
template<class Archive> \
inline void save_construct_data( \
	Archive & ar, const PlayerType * p, const unsigned int file_version \
	){ \
	ar & boost::serialization::make_nvp("index", p->index); \
	ar & boost::serialization::make_nvp("name", p->getName()); \
} \
template<class Archive> \
inline void load_construct_data( \
	Archive & ar, PlayerType * p, const unsigned int file_version \
	){ \
	pan::PlayerIndex index; \
	ar & boost::serialization::make_nvp("index", index); \
	std::string name; \
	ar & boost::serialization::make_nvp("name", name); \
	::new(p)PlayerType(index, name); \
}

namespace boost {
	namespace serialization {
		BOOST_PTR_SERIALIZE(pan::Player<pan::Roles::Dispatcher>);
		BOOST_PTR_SERIALIZE(pan::Player<pan::Roles::OperationsExpert>);
		BOOST_PTR_SERIALIZE(pan::Player<pan::Roles::Scientist>);
		BOOST_PTR_SERIALIZE(pan::Player<pan::Roles::Medic>);
		BOOST_PTR_SERIALIZE(pan::Player<pan::Roles::QSpecialist>);
		BOOST_PTR_SERIALIZE(pan::Player<pan::Roles::Researcher>);
		BOOST_PTR_SERIALIZE(pan::Player<pan::Roles::CPlanner>);
	}
}
