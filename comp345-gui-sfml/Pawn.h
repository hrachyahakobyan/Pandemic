#pragma once

namespace gui{
	class Pawn : public sf::Sprite
	{
	public:
		enum class Color{
			White = 0, Blue, Orange, Pink, Brown, Green, DarkGreen
		};
		static const std::size_t ColorCount = 7;
		Pawn(Color color, const sf::Vector2f& pos, const sf::Vector2f& size);
		Pawn(const Pawn&);
		Pawn& operator=(const Pawn&);
		~Pawn();

		inline Color getColor() const;
		void setColor(Color c);
	private:
		void updateTexture();
		Color color;
		sf::Vector2f size;
		sf::Texture pawnTexture;
	};

	Pawn::Color Pawn::getColor() const
	{
		return color;
	}
}

