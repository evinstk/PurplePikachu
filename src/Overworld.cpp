#include <TEMM/Overworld.hpp>
#include <TEMM/Mob.hpp>
#include <RapidXML/rapidxml.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include <fstream>

namespace temm
{

	Overworld::Overworld(sf::RenderTarget& target)
		: mTarget(target)
		, mSceneGraph(0)
		, mTileMap()
	{
		mSceneGraph.setScale(4.f, 4.f);
		mTileMap.setScale(4.f, 4.f);

		loadTextures();

		std::unique_ptr<Mob> red(new Mob(0, Mob::Red, mTextures));
		red->move(10.f, 10.f);
		mSceneGraph.attachChild(std::move(red));

		mTileMap.loadTexture("res/img/tiles.png");
		loadTMX("res/map/test.tmx");
	}

	void Overworld::loadTMX(const std::string& filename)
	{
		std::vector<sf::VertexArray> vertices;

		rapidxml::xml_document<> mapTMX;
		std::ifstream mapFile(filename);
		std::vector<char> buffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
		mapFile.close();
		buffer.push_back('\0');
		mapTMX.parse<0>(&buffer[0]);

		rapidxml::xml_node<>* mapNode = mapTMX.first_node();
		int width = std::atoi(mapNode->first_attribute("width")->value());
		int height = std::atoi(mapNode->first_attribute("height")->value());

		// Tile properties
		rapidxml::xml_node<>* tilesetNode = mapNode->first_node("tileset");
		int tileWidth = std::atoi(tilesetNode->first_attribute("tilewidth")->value());
		int tileHeight = std::atoi(tilesetNode->first_attribute("tileheight")->value());
		int tilesetWidth = std::atoi(tilesetNode->first_node("image")->first_attribute("width")->value());
		int tilesetHeight = std::atoi(tilesetNode->first_node("image")->first_attribute("height")->value());

		int layerIndex = 0;
		for (rapidxml::xml_node<>* layer = mapNode->first_node("layer"); layer; layer = layer->next_sibling("layer"))
		{
			vertices.push_back(sf::VertexArray());
			vertices[layerIndex].setPrimitiveType(sf::Quads);
			vertices[layerIndex].resize(width * height * 4);

			int i = 0;
			for (rapidxml::xml_node<>* tile = layer->first_node("data")->first_node("tile"); tile; tile = tile->next_sibling("tile"))
			{
				int tileID = std::atoi(tile->first_attribute("gid")->value()) - 1;

				sf::Vertex* quad = &vertices[layerIndex][i * 4];

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

				++i;
			}
			++layerIndex;
		}

		mTileMap.setVertices(std::move(vertices));
	}

	void Overworld::loadTextures()
	{
		mTextures.load(TextureID::Entities, "res/img/entities.png");
	}

	void Overworld::draw()
	{
		mTarget.draw(mTileMap);
		mTarget.draw(mSceneGraph);
	}

	bool Overworld::update(sf::Time dt)
	{
		return false;
	}

}