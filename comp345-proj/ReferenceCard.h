#pragma once

namespace pan{
	/**
	*	@brief A singleton class representing the reference class entity.
	*	Note it does not inherit the Card class since
	*	strictly speaking, ReferenceCard is	just a container for strings
	*	and does not have to do anything with the game mechanics.
	*/
	class ReferenceCard
	{
	public:
		static ReferenceCard& getInstance()
		{
			static ReferenceCard instance; 
			return instance;
		}

	public:
		const std::string description = "Description of the reference card";
	private:
		ReferenceCard(const ReferenceCard&);
		ReferenceCard& operator=(const ReferenceCard&);
		ReferenceCard(){}
	};
}

