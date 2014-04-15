#include <TEMM/DataTables.hpp>
#include <TEMM/Mob.hpp>

namespace temm
{

	std::vector<MobData> initializeMobData()
	{
		std::vector<MobData> data(Mob::TypeCount);

		data[Mob::Red].texture = TextureID::Entities;
		data[Mob::Red].textureRect = sf::IntRect(0, 0, 16, 19);

		return data;
	}

}