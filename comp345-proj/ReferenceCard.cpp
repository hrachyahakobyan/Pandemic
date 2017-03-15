#include "stdafx.h"
#include "ReferenceCard.h"

namespace pan{
	const std::string ReferenceCard::descriptionText = "1. Drive/Ferry \n Move to a city connected by a white line. \n\
				2. Direct flight \n Discard a city card to move to the city named on the card. \n\
				3. Charter flight \n Discard a city card that matches the city you are in to move to any city. \n\
				4. Shuttle flight \n Move from a city with a research station to any other city with a research stationc.";


	ReferenceCard::ReferenceCard() :
		description(ReferenceCard::descriptionText)
	{
	}
}