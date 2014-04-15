#include <TEMM/Overworld.hpp>
#include <TEMM/Mob.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

namespace temm
{

	Overworld::Overworld(sf::RenderTarget& target, Tile defaultTile, int height, int width)
		: mTarget(target)
		, mSceneGraph(0)
		, mTiles(height * width)
		, mWidth(width)
		, mHeight(height)
	{
		for (auto& tile : mTiles)
		{
			tile = defaultTile;
		}

		mSceneGraph.setScale(4.f, 4.f);

		loadTextures();
		std::unique_ptr<Mob> red(new Mob(0, Mob::Red, mTextures));
		red->move(10.f, 10.f);
		mSceneGraph.attachChild(std::move(red));
	}

	void Overworld::loadTextures()
	{
		mTextures.load(TextureID::Entities, "res/img/entities.png");
	}

	void Overworld::draw()
	{
		mTarget.draw(mSceneGraph);
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