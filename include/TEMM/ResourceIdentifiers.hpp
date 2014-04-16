#ifndef TEMM_RESOURCE_IDENTIFIERS_HPP
#define TEMM_RESOURCE_IDENTIFIERS_HPP

namespace sf
{
	class Texture;
}

namespace temm
{

	enum class TextureID
	{
		Entities,
		Tiles,
	};

	template <typename Resource, typename Identifier>
	class ResourceHolder;

	typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;
}

#endif