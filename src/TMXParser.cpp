#include <TEMM/TMXParser.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <fstream>
#include <vector>

namespace temm
{

	TMXParser::TMXParser()
		: mTMX()
		, mBuffer()
	{
	}

	void TMXParser::load(const std::string& filename)
	{
		std::ifstream mapFile(filename);
		mBuffer.clear();
		mBuffer = std::vector<char>(std::istreambuf_iterator<char>(mapFile), std::istreambuf_iterator<char>());
		mapFile.close();
		mBuffer.push_back('\0');
		mTMX.parse<0>(&mBuffer[0]);
	}

	int TMXParser::getWidth() const
	{
		return std::atoi(mTMX.first_node("map")->first_attribute("width")->value());
	}

	int TMXParser::getHeight() const
	{
		return std::atoi(mTMX.first_node()->first_attribute("height")->value());
	}

	int TMXParser::getTileWidth() const
	{
		return std::atoi(mTMX.first_node()->first_node("tileset")->first_attribute("tilewidth")->value());
	}

	int TMXParser::getTileHeight() const
	{
		return std::atoi(mTMX.first_node()->first_node("tileset")->first_attribute("tileheight")->value());
	}

	int TMXParser::getTilesetWidth() const
	{
		return std::atoi(mTMX.first_node()->first_node("tileset")->first_node("image")->first_attribute("width")->value());
	}

	int TMXParser::getTilesetHeight() const
	{
		return std::atoi(mTMX.first_node()->first_node("tileset")->first_node("image")->first_attribute("height")->value());
	}

	TileLayers TMXParser::getTileLayers() const
	{
		TileLayers layers;

		int index = 0;
		for (rapidxml::xml_node<>* node = mTMX.first_node()->first_node(); node; node = node->next_sibling())
		{
			// If it's an objectgroup or imagelayer, increment
			// the index for any upcoming tile layers
			if (strcmp(node->name(), "objectgroup") == 0 || strcmp(node->name(), "imagelayer") == 0)
			{
				++index;
			}
			else if (strcmp(node->name(), "layer") == 0)
			{
				std::vector<int>& currLayer = layers[index++];
				for (rapidxml::xml_node<>* tile = node->first_node("data")->first_node("tile"); tile; tile = tile->next_sibling("tile"))
				{	
					currLayer.push_back(std::atoi(tile->first_attribute("gid")->value()));
				}
			}
		}

		return layers;
	}

	ObjectLayers TMXParser::getObjectLayers() const
	{
		ObjectLayers layers;

		int index = 0;
		for (rapidxml::xml_node<>* node = mTMX.first_node()->first_node(); node; node = node->next_sibling())
		{
			// If it's a layer or imagelayer, increment
			// the index for any upcoming tile layers
			if (strcmp(node->name(), "layer") == 0 || strcmp(node->name(), "imagelayer") == 0)
			{
				++index;
			}
			else if (strcmp(node->name(), "objectgroup") == 0)
			{
				std::vector<NodeObject>& currLayer = layers[index++];
				for (rapidxml::xml_node<>* objectNode = node->first_node("object"); objectNode; objectNode = objectNode->next_sibling("object"))
				{
					std::string type = objectNode->first_attribute("type")->value();
					int x = std::atoi(objectNode->first_attribute("x")->value());
					int y = std::atoi(objectNode->first_attribute("y")->value());
					bool isPlayer = false;
					if (objectNode->first_attribute("name"))
					{
						if (std::strcmp(objectNode->first_attribute("name")->value(), "Player") == 0)
						{
							isPlayer = true;
						}
					}
					currLayer.push_back(NodeObject(type, x, y, isPlayer));
				}
			}
		}

		return layers;
	}

	int TMXParser::getNumLayers() const
	{
		int count = 0;
		for (rapidxml::xml_node<>* node = mTMX.first_node()->first_node(); node; node = node->next_sibling())
		{
			if (strcmp(node->name(), "layer") == 0 || strcmp(node->name(), "imagelayer") == 0 || strcmp(node->name(), "objectgroup"))
			{
				++count;
			}
		}
		return count;
	}

}
