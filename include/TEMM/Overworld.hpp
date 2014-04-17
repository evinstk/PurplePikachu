#ifndef OVERWORLD_HPP
#define OVERWORLD_HPP

#include <TEMM/SceneNode.hpp>
#include <TEMM/ResourceHolder.hpp>
#include <TEMM/ResourceIdentifiers.hpp>
#include <TEMM/TileMap.hpp>
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

		enum class Layer
		{
			Air,
			Ground,
			LayerCount,
		};

		Overworld(sf::RenderTarget& target);

		void loadMap(const std::string& filename);

		void draw();
		bool update(sf::Time dt);

	private:
		void loadTextures();
		void resolveCollisions();

		sf::RenderTarget& mTarget;
		TextureHolder mTextures;
		SceneNode mSceneGraph;
		TileMap mTileMap;
	};

}

#endif