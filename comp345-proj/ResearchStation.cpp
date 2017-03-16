#include "stdafx.h"
#include "ResearchStation.h"

namespace gui{
	ResearchStation::ResearchStation(const sf::Vector2f& pos) 
	{
		this->setPosition(pos);
	}

	ResearchStation::ResearchStation(const ResearchStation& o) :
    texture(o.texture)
	{
		setTexture(texture);
	}

	ResearchStation& ResearchStation::operator=(const ResearchStation& o)
	{
		this->texture = o.texture;
		setTexture(texture);
		return *this;
	}

	ResearchStation::~ResearchStation()
	{
	}
}
