#ifndef OVERWORLD_HPP
#define OVERWORLD_HPP

#include <TEMM/SceneNode.hpp>
#include <TEMM/ResourceHolder.hpp>
#include <TEMM/ResourceIdentifiers.hpp>
#include <vector>

namespace sf
{
	class Time;
}

namespace temm
{

	class Overworld : private sf::NonCopyable
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

		Overworld(sf::RenderTarget& target, Tile defaultTile, int width, int height);

		void draw();
		bool update(sf::Time dt);

		Tile getTile(int x, int y) const;
		int getWidth() const;
		int getHeight() const;

	private:
		void loadTextures();
		void resolveCollisions();

		sf::RenderTarget& mTarget;
		TextureHolder mTextures;
		SceneNode mSceneGraph;

		std::vector<Tile> mTiles;
		const int mWidth;
		const int mHeight;
	};

}

#endif