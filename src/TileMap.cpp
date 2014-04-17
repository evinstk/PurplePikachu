#include <TEMM/TileMap.hpp>
#include <TEMM/DataTables.hpp>
#include <RapidXML/rapidxml.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream>
#include <array>

namespace temm
{

	namespace
	{
		const std::map<int, TileData> Table = initializeTileData();
	}

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

	void TileMap::loadMap(const std::string& filename)
	{
		rapidxml::xml_document<> mapTMX;
		std::ifstream mapFile(filename);
		std::vector<char> buffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
		mapFile.close();
		buffer.push_back('\0');
		mapTMX.parse<0>(&buffer[0]);

		rapidxml::xml_node<>* mapNode = mapTMX.first_node();

		rapidxml::xml_node<>* tileNode = mapNode->first_node("tileset");
		mWidth = std::atoi(mapNode->first_attribute("width")->value());
		mHeight = std::atoi(mapNode->first_attribute("height")->value());

		mVertices.clear();

		int layerIndex = 0;
		for (rapidxml::xml_node<>* layer = mapNode->first_node("layer"); layer; layer = layer->next_sibling("layer"))
		{
			mVertices.push_back(sf::VertexArray());
			mVertices[layerIndex].setPrimitiveType(sf::Quads);
			mVertices[layerIndex].resize(mWidth * mHeight * 4);

			int i = 0;
			for (rapidxml::xml_node<>* tile = layer->first_node("data")->first_node("tile"); tile; tile = tile->next_sibling("tile"))
			{
				int tileID = std::atoi(tile->first_attribute("gid")->value());
				sf::IntRect textureRect = Table.at(tileID).textureRect;

				sf::Vertex* quad = &mVertices[layerIndex][i * 4];

				sf::Vector2f topLeft(float(i % mWidth) * TileSize, (float)(i / mWidth) * TileSize);
				quad[0].position = topLeft;
				quad[1].position = topLeft + sf::Vector2f((float)TileSize, 0.f);
				quad[2].position = topLeft + sf::Vector2f((float)TileSize, (float)TileSize);
				quad[3].position = topLeft + sf::Vector2f(0.f, (float)TileSize);

				sf::Vector2f texTopLeft((float)textureRect.left, (float)textureRect.top);
				quad[0].texCoords = texTopLeft;
				quad[1].texCoords = texTopLeft + sf::Vector2f((float)TileSize, 0.f);
				quad[2].texCoords = texTopLeft + sf::Vector2f((float)TileSize, (float)TileSize);
				quad[3].texCoords = texTopLeft + sf::Vector2f(0.f, (float)TileSize);

				++i;
			}
			++layerIndex;
		}
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &mTexture;
		for (auto& vArray : mVertices)
			target.draw(vArray, states);
	}

}