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

		const std::string description = "1. Drive/Ferry \n Move to a city connected by a white line. \n\
										 2. Direct flight \n Discard a city card to move to the city named on the card. \n\
										 3. Charter flight \n Discard a city card that matches the city you are in to move to any city. \n\
										 4. Shuttle flight \n Move from a city with a research station to any other city with a research stationc.";
	private:
		ReferenceCard(const ReferenceCard&);
		ReferenceCard& operator=(const ReferenceCard&);
		ReferenceCard(){}
	};
}

