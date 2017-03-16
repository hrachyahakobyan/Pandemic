#include "stdafx.h"
#include "MapView.h"
#include "CityView.h"
#include "City.h"
#include "Pawn.h"

namespace gui{
	MapView::MapView() 
	{
		mapTexture.loadFromFile(filename);
		mapSprite.setTexture(mapTexture);
		cities.push_back(CityView({ 50.f, 50.f }, 30.f));
		pan::City city;
		city.addPlayer(0);
		city.addPlayer(1);
		city.addPlayer(2);
		cities[0].update(city);
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
