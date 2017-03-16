#pragma once
namespace gui{
	class CityView;
	class MapView : public sf::Drawable, public::sf::Transformable
	{
	public:
		MapView();
		MapView(const MapView&) = delete;
		MapView& operator=(const MapView&) = delete;
		~MapView();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		std::string filename = "resources/map.png";
		sf::Sprite mapSprite;
		sf::Texture mapTexture;
		std::vector<CityView> cities;
	};
}


