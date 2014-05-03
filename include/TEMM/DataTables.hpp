#ifndef TEMM_DATA_TABLES_HPP
#define TEMM_DATA_TABLES_HPP

#include <TEMM/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <map>

namespace temm
{

	struct MobData
	{
		std::string texture;
		sf::IntRect collisionRect;
		sf::IntRect headRect;
	};

	std::vector<MobData> initializeMobData();

}

#endif