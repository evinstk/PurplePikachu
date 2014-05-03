#ifndef TEMM_RESOURCE_IDENTIFIERS_HPP
#define TEMM_RESOURCE_IDENTIFIERS_HPP

#include <string>

namespace sf
{
	class Texture;
}

namespace temm
{

	template <typename Resource, typename Identifier>
	class ResourceHolder;

	typedef ResourceHolder<sf::Texture, std::string> TextureHolder;
}

#endif
