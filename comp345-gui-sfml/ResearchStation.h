#pragma once

namespace gui{
	class ResearchStation : public sf::Sprite
	{
	public:
		ResearchStation(const sf::Vector2f& pos);
		ResearchStation(const ResearchStation&);
		ResearchStation& operator=(const ResearchStation&);
		~ResearchStation();
	private:
		sf::Texture texture;
	};
}

