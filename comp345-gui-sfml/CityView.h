#pragma once
#include "Pawn.h"

namespace pan{
	class City;
}

namespace gui{
	class ResearchStation;

	class CityView : public sf::Drawable, public sf::Transformable
	{
	public:
		CityView(const sf::Vector2f& position, unsigned int radius);
		~CityView();
	
		void update(const pan::City& city);

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		std::vector<Pawn> pawns;
		std::shared_ptr<ResearchStation> station;
		unsigned int radius;
		void updatePawnPositions();
	};
}

