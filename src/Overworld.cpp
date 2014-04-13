#include <TEMM/Overworld.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

namespace temm
{

	Overworld::Overworld(Tile defaultTile, int height, int width)
		: mTiles(height * width)
		, mWidth(width)
		, mHeight(height)
	{
		for (auto& tile : mTiles)
		{
			tile = defaultTile;
		}
	}

	bool Overworld::update(sf::Time dt)
	{
		return false;
	}

	Overworld::Tile Overworld::getTile(int x, int y) const
	{
		assert((x < mWidth) && (y < mHeight));
		long index = x + (y * mWidth);
		return mTiles[index];
	}

	int Overworld::getWidth() const
	{
		return mWidth;
	}

	int Overworld::getHeight() const
	{
		return mHeight;
	}

}