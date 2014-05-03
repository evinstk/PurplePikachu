#ifndef OVERWORLD_HPP
#define OVERWORLD_HPP

#include <TEMM/SceneNode.hpp>
#include <TEMM/ResourceHolder.hpp>
#include <TEMM/ResourceIdentifiers.hpp>
#include <TEMM/TileMap.hpp>
#include <TEMM/NodeFactory.hpp>
#include <TEMM/CommandQueue.hpp>
#include <TEMM/TMXParser.hpp>
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

		CommandQueue& getCommandQueue();

		void loadTextures(const std::string& textureID, const std::string& filename);
		void loadTMX(const std::string& filename);

		void draw();
		void update(sf::Time dt);

	private:
		void loadNodeFactory();

		sf::RenderTarget& mTarget;
		TextureHolder mTextures;
		NodeFactory mNodeFactory;
		SceneNode mSceneGraph;
		std::vector<sf::Drawable*> mLayers;
		std::vector<TileMap::Ptr> mTileMaps;
		int mNumLayers;

		CommandQueue mCommandQueue;

	};

}

#endif
