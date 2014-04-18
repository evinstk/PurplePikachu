#ifndef OVERWORLD_HPP
#define OVERWORLD_HPP

#include <TEMM/SceneNode.hpp>
#include <TEMM/ResourceHolder.hpp>
#include <TEMM/ResourceIdentifiers.hpp>
#include <TEMM/TileMap.hpp>
#include <TEMM/NodeFactory.hpp>
#include <TEMM/CommandQueue.hpp>
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

		void loadTMX(const std::string& filename);

		void draw();
		void update(sf::Time dt);

	private:
		void loadTextures();
		void loadNodeFactory();

		void resolveCollisions();

		sf::RenderTarget& mTarget;
		TextureHolder mTextures;
		NodeFactory mNodeFactory;
		SceneNode mSceneGraph;
		TileMap mTileMap;

		CommandQueue mCommandQueue;
	};

}

#endif
