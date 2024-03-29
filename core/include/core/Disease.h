#pragma once
namespace pan{
	/**
	*	@brief Stores disease state.
	*	@author Hrachya Hakobyan
	*/
	class Disease 
	{
	public:
		Disease(DiseaseType diseaseType = 0);
		Disease(const Disease&);
		Disease& operator=(const Disease&);
		~Disease() = default;

		inline bool getIsCured() const;
		inline bool getIsEradicated() const;
		inline DiseaseType getDiseaeType() const;

		void setIsCured(bool isCured);
		void setIsEradicated(bool isEradicated);

		std::string description() const;

		inline bool operator==(const Disease&) const;
		inline bool operator!=(const Disease&) const;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar  & boost::serialization::make_nvp("diseaseType", const_cast<DiseaseType&>(diseaseType));
			ar  & BOOST_SERIALIZATION_NVP(isCured);
			ar  & BOOST_SERIALIZATION_NVP(isEradicated);
		}
	private:
		DiseaseType diseaseType;
		bool isCured;
		bool isEradicated;
	};

	bool Disease::operator==(const Disease& o) const
	{
		return (this->diseaseType == o.diseaseType && this->isCured == o.isCured && this->isEradicated == o.isEradicated);
	}

	bool Disease::operator!=(const Disease& o) const
	{
		return !((*this) == o);
	}

	bool Disease::getIsCured() const
	{
		return isCured;
	}

	bool Disease::getIsEradicated() const
	{
		return isEradicated;
	}

	DiseaseType Disease::getDiseaeType() const
	{
		return diseaseType;
	}
}

