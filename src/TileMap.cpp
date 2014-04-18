#include <TEMM/TileMap.hpp>
#include <TEMM/DataTables.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <array>

namespace temm
{

	TileMap::TileMap()
		: mWidth(0)
		, mHeight(0)
		, mTexture()
	{
	}

	void TileMap::loadTexture(const std::string& filename)
	{
		mTexture.loadFromFile(filename);
	}

	void TileMap::setVertices(const std::vector<sf::VertexArray>& vArray)
	{
		mVertices.clear();
		mVertices.resize(vArray.size());
		for (unsigned i = 0; i < vArray.size(); ++i)
		{
			for (unsigned j = 0; j < vArray[i].getVertexCount(); ++j)
			{
				mVertices[i].append(vArray[i][j]);
			}
		}
	}

	void TileMap::setVertices(std::vector<sf::VertexArray>&& vArray)
	{
		mVertices.clear();
		mVertices = std::move(vArray);
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &mTexture;
		for (auto& vArray : mVertices)
			target.draw(vArray, states);
	}

}