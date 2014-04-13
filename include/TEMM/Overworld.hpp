#ifndef OVERWORLD_HPP
#define OVERWORLD_HPP

#include <vector>

namespace sf
{
	class Time;
}

namespace temm
{

	class Overworld
	{
	public:

		enum class Tile
		{
			Grass,
			Dirt,
			Water,
			Count,
		};

		enum class Layer
		{
			Air,
			Ground,
			LayerCount,
		};

		Overworld(Tile defaultTile, int width, int height);

		bool update(sf::Time dt);

		Tile getTile(int x, int y) const;
		int getWidth() const;
		int getHeight() const;

	private:
		void resolveCollisions();

		std::vector<Tile> mTiles;
		const int mWidth;
		const int mHeight;
	};

}

#endif