#include <TEMM/DataTables.hpp>
#include <TEMM/Mob.hpp>
#include <TEMM/TileMap.hpp>

namespace temm
{

	std::vector<MobData> initializeMobData()
	{
		std::vector<MobData> data(Mob::TypeCount);

		data[Mob::Red].texture = "entities";
		data[Mob::Red].collisionRect = sf::IntRect(0, 3, 16, 16);
		data[Mob::Red].headRect = sf::IntRect(0, 0, 16, 3);

		return data;
	}

}
