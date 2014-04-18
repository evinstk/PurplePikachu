#ifndef TEMM_TILEMAP_HPP
#define TEMM_TILEMAP_HPP

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

		void setVertices(const std::vector<sf::VertexArray>& vArray);
		void setVertices(std::vector<sf::VertexArray>&& vArray);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		int mWidth;
		int mHeight;
		int mTilesetWidth;
		int mTilesetHeight;
		int mTileWidth;
		int mTileHeight;

		std::vector<sf::VertexArray> mVertices;
		sf::Texture mTexture;
	};

}

#endif