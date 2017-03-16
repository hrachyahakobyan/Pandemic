#include "stdafx.h"
#include "CityView.h"
#include "ResearchStation.h"
#include <core/Core.hpp>

namespace gui{
	CityView::CityView(const sf::Vector2f& pos, unsigned int radius) :
		radius(radius)
	{
		this->setPosition(pos);
	}

	CityView::~CityView()
	{
	}

	void CityView::update(const pan::City& city)
	{
		pawns.clear();
		station.reset();
		for (auto p : city.getPlayers()){
			pawns.push_back(Pawn(Pawn::Color::Blue, getPosition(), sf::Vector2f(30, 30)));
		}
		if (city.researchStation)
			station.reset(new ResearchStation(getPosition()));
		updatePawnPositions();
	}

	void CityView::updatePawnPositions()
	{
		float angle = 0;
		float delta = static_cast<float>(2 * 3.14159265358979323846 / pawns.size());
		auto pos = getPosition();
		for (std::size_t i = 0; i < pawns.size(); i++){
			pawns[i].move({ pos.x + radius * std::cosf(angle), pos.y + radius * std::sinf(angle) });
		    angle += delta;
		}
	}

	void CityView::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		for (const auto& pawn : pawns){
			target.draw(pawn, states);
		}
		if (station){
			target.draw(*station.get(), states);
		}
	}
}
