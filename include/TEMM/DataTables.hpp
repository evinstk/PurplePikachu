#ifndef TEMM_DATA_TABLES_HPP
#define TEMM_DATA_TABLES_HPP

#include <TEMM/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace temm
{

	struct MobData
	{
		TextureID texture;
		sf::IntRect collisionRect;
		sf::IntRect headRect;
	};

	struct TileData
	{
		TextureID texture;
		sf::IntRect textureRect;
	};

	std::vector<MobData> initializeMobData();
	std::vector<TileData> initializeTileData();

}

#endif