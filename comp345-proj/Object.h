#pragma once

namespace pan{
	/**
	*	@brief Abstract parent class to all entities directly
	*	connected with the game state and have to be saved and loaded.
	*/
	class Object 
	{
	public:
		Object(){}
		virtual ~Object(){};
		virtual std::string description() const = 0; 
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
		}
	};
}


