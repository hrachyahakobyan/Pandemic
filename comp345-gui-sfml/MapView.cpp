#include "stdafx.h"
#include "MapView.h"
#include "CityView.h"
#include "Pawn.h"

namespace gui{
	MapView::MapView() 
	{
		mapTexture.loadFromFile(filename);
		mapSprite.setTexture(mapTexture);
	}

	MapView::~MapView()
	{
	}

	void MapView::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mapSprite, states);
		for (const auto& city : cities){
			target.draw(city, states);
		}
	}
}
