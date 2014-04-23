#ifndef TEMM_TILEMAP_HPP
#define TEMM_TILEMAP_HPP

#include <TEMM/Typedefs.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace temm
{

	class TileMap : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:
		TileMap();

		void loadTexture(const std::string& filename);

		void setMapData(int width, int height, int tileWidth, int tileHeight, int tilesetWidth, const TileLayers& tiles);
		void setMapData(int width, int height, int tileWidth, int tileHeight, int tilesetWidth, TileLayers&& tiles);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		std::map<int, sf::VertexArray> mVertices;
		sf::Texture mTexture;
	};

}

#endif
