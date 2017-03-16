#include "stdafx.h"
#include "Pawn.h"

namespace gui{
	Pawn::Pawn(Color c, const sf::Vector2f& pos, const sf::Vector2f& size)  :
		size(size)
	{
		this->setColor(c);
		this->setPosition(pos);
		updateTexture();
	}

	Pawn::Pawn(const Pawn& o) :
		color(o.color), pawnTexture(o.pawnTexture), size(o.size)
	{
		updateTexture();
	}

	Pawn& Pawn::operator=(const Pawn& o)
	{
		this->color = o.color;
		this->pawnTexture = o.pawnTexture;
		this->size = o.size;
		updateTexture();
		return *this;
	}

	Pawn::~Pawn()
	{
	}

	void Pawn::setColor(Color c)
	{
		color = c;
		std::string filename = "resources/pawn" + std::to_string(static_cast<std::underlying_type<Color>::type>(color)) + ".png";
		pawnTexture.loadFromFile(filename);
	}

	void Pawn::updateTexture()
	{
		sf::Vector2f scale(size.x / pawnTexture.getSize().x, size.y / pawnTexture.getSize().y);
		setScale(scale);
		setTexture(pawnTexture);
	}
}
