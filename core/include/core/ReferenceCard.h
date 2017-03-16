#pragma once

namespace pan{
	/**
	*	@brief	Class representing the ReferenceCard.
	*	Note it is not derived from the base Card class 
	*	since it does not play any role in the game mechanics.
	*/
	class ReferenceCard
	{
	public:
		ReferenceCard();
		const std::string& description;
	private:
		static const std::string descriptionText;
	};
}

