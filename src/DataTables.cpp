#include <TEMM/DataTables.hpp>
#include <TEMM/Mob.hpp>
#include <TEMM/TileMap.hpp>

namespace temm
{

	std::vector<MobData> initializeMobData()
	{
		std::vector<MobData> data(Mob::TypeCount);

		data[Mob::Red].texture = TextureID::Entities;
		data[Mob::Red].collisionRect = sf::IntRect(0, 3, 16, 16);
		data[Mob::Red].headRect = sf::IntRect(0, 0, 16, 3);

		return data;
	}

	std::map<int, TileData> initializeTileData()
	{
		std::map<int, TileData> data;

		int s = TileMap::TileSize;

		data[TileMap::Grass].textureRect = sf::IntRect(s * 1, s * 3, s, s);

		data[TileMap::GrassRidgeLeftTop].textureRect = sf::IntRect(0, s * 1, s, s);

		data[TileMap::GrassRidgeLeft].textureRect = sf::IntRect(0, s * 2, s, s);

		data[TileMap::GrassRidgeLeftBottom].textureRect = sf::IntRect(0, s * 3, s, s);

		data[TileMap::GrassRidgeRightTop].textureRect = sf::IntRect(s * 4, s * 1, s, s);

		data[TileMap::GrassRidgeRight].textureRect = sf::IntRect(s * 4, s * 2, s, s);

		data[TileMap::GrassRidgeRightBottom].textureRect = sf::IntRect(s * 4, s * 3, s, s);

		data[TileMap::GrassRidgeBottomLeft].textureRect = sf::IntRect(s * 1, s * 4, s, s);

		data[TileMap::GrassRidgeBottom].textureRect = sf::IntRect(s * 2, s * 4, s, s);

		data[TileMap::GrassRidgeBottomRight].textureRect = sf::IntRect(s * 3, s * 4, s, s);

		data[TileMap::GrassCornerBottomLeft].textureRect = sf::IntRect(0, s * 4, s, s);

		data[TileMap::GrassCornerBottomRight].textureRect = sf::IntRect(s * 4, s * 4, s, s);

		data[TileMap::GrassCornerTopLeft].textureRect = sf::IntRect(0, 0, s, s);

		data[TileMap::GrassCornerTopRight].textureRect = sf::IntRect(s * 4, 0, s, s);

		return data;
	}

}