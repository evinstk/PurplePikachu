#ifndef TEMM_TMX_PARSER_HPP
#define TEMM_TMX_PARSER_HPP

#include <TEMM/Typedefs.hpp>
#include <RapidXML/rapidxml.hpp>
#include <string>
#include <map>

namespace sf
{
	class VertexArray;
}

namespace temm
{

	class TMXParser
	{
	public:
		TMXParser();

		void load(const std::string& filename);

		int getWidth() const;
		int getHeight() const;
		int getTileWidth() const;
		int getTileHeight() const;
		int getTilesetWidth() const;
		int getTilesetHeight() const;

		TileLayers getTileLayers() const;
		ObjectLayers getObjectLayers() const;

	private:
		rapidxml::xml_document<> mTMX;
		std::vector<char> mBuffer;
	};

}

#endif
