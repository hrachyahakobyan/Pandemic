#pragma once
#include "Object.h"
#include "Role.h"
#include "Map.h"
#include "common.h"

namespace pan{
	class ReferenceCard;

	/**
	*	@brief Base class for player objects.
	*	@author Hrachya Hakobyan
	*/
	class PlayerBase : public Object{
	public:
		virtual ~PlayerBase();

		inline bool operator==(const PlayerBase&) const;
		inline bool operator!=(const PlayerBase&) const;

		inline const std::string& getName() const;
		inline void setName(const std::string& name);

		inline Map::CityIndex getLocation() const;
		inline void setLocation(Map::CityIndex);

		std::string description() const;

		const RoleBase role;
		const ReferenceCard& referenceCard;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object);
			ar & BOOST_SERIALIZATION_NVP(name);
		}
	protected:
		PlayerBase();
		PlayerBase(const RoleBase& role);
		PlayerBase(const RoleBase& role, const std::string& name);

		std::string name;
		Map::CityIndex location;
#ifdef _DEBUG
		friend class PlayerTest;
		FRIEND_TEST(PlayerTest, compares);
		FRIEND_TEST(PlayerTest, serializes);
		FRIEND_TEST(PlayerTest, serializesContainer);
#endif
	};

	bool PlayerBase::operator==(const PlayerBase& o) const
	{
		return (this->role == o.role && this->name == o.name);
	}

	bool PlayerBase::operator!=(const PlayerBase& o) const
	{
		return !((*this) == o);
	}

	const std::string& PlayerBase::getName() const
	{
		return name;
	}

	void PlayerBase::setName(const std::string& name)
	{
		this->name = name;
	}

	Map::CityIndex PlayerBase::getLocation() const
	{
		return location;
	}

	void PlayerBase::setLocation(Map::CityIndex loc)
	{
		this->location = loc;
	}

	
}

