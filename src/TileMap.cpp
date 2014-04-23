#include <TEMM/TileMap.hpp>
#include <TEMM/DataTables.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <array>

namespace temm
{

	TileMap::TileMap()
		: mTexture()
	{
	}

	void TileMap::loadTexture(const std::string& filename)
	{
		mTexture.loadFromFile(filename);
	}

	void TileMap::setMapData(int width, int height, int tileWidth, int tileHeight, int tilesetWidth, const TileLayers& tileLayers)
	{
		mVertices.clear();
		for (auto& layer : tileLayers)
		{
			sf::VertexArray& currVertexArray = mVertices[layer.first];
			currVertexArray.resize(layer.second.size() * 4);
			currVertexArray.setPrimitiveType(sf::Quads);
			for (unsigned i = 0; i < layer.second.size(); ++i)
			{
				// TODO: Account for multiple tilesets
				int tileID = layer.second[i] - 1;

				sf::Vertex* quad = &currVertexArray[i * 4];

				sf::Vector2f topLeft(float(i % width) * tileWidth, (float)(i / width) * tileHeight);
				quad[0].position = topLeft;
				quad[1].position = topLeft + sf::Vector2f((float)tileWidth, 0.f);
				quad[2].position = topLeft + sf::Vector2f((float)tileWidth, (float)tileHeight);
				quad[3].position = topLeft + sf::Vector2f(0.f, (float)tileHeight);

				sf::Vector2f texTopLeft((float)((tileID * tileWidth) % tilesetWidth), (float)(((tileID * tileWidth) / tilesetWidth) * tileHeight));
				quad[0].texCoords = texTopLeft;
				quad[1].texCoords = texTopLeft + sf::Vector2f((float)tileWidth, 0.f);
				quad[2].texCoords = texTopLeft + sf::Vector2f((float)tileWidth, (float)tileHeight);
				quad[3].texCoords = texTopLeft + sf::Vector2f(0.f, (float)tileHeight);
			}
		}
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &mTexture;
		for (auto& vArray : mVertices)
			target.draw(vArray.second, states);
	}

}