#include <TEMM/Overworld.hpp>
#include <TEMM/Mob.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

namespace temm
{

	Overworld::Overworld(sf::RenderTarget& target)
		: mTarget(target)
		, mSceneGraph(0)
		, mTileMap()
	{
		mSceneGraph.setScale(4.f, 4.f);
		mTileMap.setScale(4.f, 4.f);

		loadTextures();

		std::unique_ptr<Mob> red(new Mob(0, Mob::Red, mTextures));
		red->move(10.f, 10.f);
		mSceneGraph.attachChild(std::move(red));

		mTileMap.loadTexture(mTextures.get(TextureID::Tiles));
		mTileMap.loadMap("res/map/test.tmx");
	}

	void Overworld::loadMap(const std::string& filename)
	{
		mTileMap.loadMap(filename);
	}

	void Overworld::loadTextures()
	{
		mTextures.load(TextureID::Entities, "res/img/entities.png");
		mTextures.load(TextureID::Tiles, "res/img/tiles.png");
	}

	void Overworld::draw()
	{
		mTarget.draw(mTileMap);
		mTarget.draw(mSceneGraph);
	}

	bool Overworld::update(sf::Time dt)
	{
		return false;
	}

}