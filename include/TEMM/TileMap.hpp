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
		enum Tile
		{
			Grass = 17,

			GrassRidgeLeftTop = 6,
			GrassRidgeLeft = 11,
			GrassRidgeLeftBottom = 16,

			GrassRidgeRightTop = 10,
			GrassRidgeRight = 15,
			GrassRidgeRightBottom = 20,

			GrassRidgeBottomLeft = 22,
			GrassRidgeBottom = 23,
			GrassRidgeBottomRight = 24,

			GrassCornerBottomLeft = 21,
			GrassCornerBottomRight = 25,

			GrassCornerTopLeft = 1,
			GrassCornerTopRight = 5,

			TypeCount = 14,
		};

		static const int TileSize = 16;

		TileMap();

		void loadTexture(const std::string& filename);
		void loadMap(const std::string& filename);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		int mWidth;
		int mHeight;
		std::vector<sf::VertexArray> mVertices;
		sf::Texture mTexture;
	};

}

#endif