#ifndef TEMM_TILEMAP_HPP
#define TEMM_TILEMAP_HPP

#include <TEMM/Typedefs.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <memory>

namespace temm
{

	class TileMap : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:
		typedef std::unique_ptr<TileMap> Ptr;

		TileMap();

		void loadTexture(const std::string& filename);

		void setMapData(int width, int height, int tileWidth, int tileHeight, int tilesetWidth, const std::vector<int>& tiles);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::VertexArray mVertices;
		sf::Texture mTexture;
	};

}

#endif
