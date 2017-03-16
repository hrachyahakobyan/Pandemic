#pragma once
#include "Object.h"

namespace pan
{
	/**
	*	@brief Class to represent a region on the map.
	*	Must be default constructible and assignable.
	*	@author Hrachya Hakobyan
	*/
	class Region : public Object{
	public:
		inline const std::string& getName() const;
		inline void setName(const std::string& name);
		inline std::string description() const;

		inline bool operator==(const Region& other) const;
		inline bool operator!=(const Region& other) const;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object);
			ar & BOOST_SERIALIZATION_NVP(name);
		}
	private:
		std::string name;
	};

	bool Region::operator==(const Region& other) const
	{
		return name == other.name;
	}

	bool Region::operator!=(const Region& other) const
	{
		return !((*this) == other);
	}

	const std::string& Region::getName() const
	{
		return name;
	}

	void Region::setName(const std::string& name)
	{
		this->name = name;
	}

	std::string Region::description() const
	{
		return "Region name: " + name;
	}
}

