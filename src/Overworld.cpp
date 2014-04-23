#include <TEMM/Overworld.hpp>
#include <TEMM/Mob.hpp>
#include <TEMM/Typedefs.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include <fstream>

namespace temm
{

	Overworld::Overworld(sf::RenderTarget& target)
		: mTarget(target)
		, mTextures()
		, mNodeFactory()
		, mSceneGraph(0)
		, mTileMap()
		, mTMXParser()
	{
		mSceneGraph.setScale(4.f, 4.f);
		mTileMap.setScale(4.f, 4.f);

		loadTextures();
		loadNodeFactory();

		mTileMap.loadTexture("res/img/tiles.png");
		loadTMX("res/map/test.tmx");
	}

	CommandQueue& Overworld::getCommandQueue()
	{
		return mCommandQueue;
	}

	void Overworld::loadTMX(const std::string& filename)
	{
		std::vector<sf::VertexArray> vertices;

		mTMXParser.load(filename);

		int width(mTMXParser.getWidth());
		int height(mTMXParser.getHeight());
		int tileWidth(mTMXParser.getTileWidth());
		int tileHeight(mTMXParser.getTileHeight());
		int tilesetWidth(mTMXParser.getTilesetWidth());
		TileLayers tileLayers(mTMXParser.getTileLayers());
		mTileMap.setMapData(width, height, tileWidth, tileHeight, tilesetWidth, tileLayers);

		ObjectLayers objectLayers(mTMXParser.getObjectLayers());
		for (auto& objectLayer : objectLayers)
		{
			for (auto& object : objectLayer.second)
			{
				SceneNode::Ptr sceneNode = mNodeFactory.get(object.type);
				sceneNode->setPosition((float)object.x, (float)object.y);
				if (object.isPlayer)
				{
					assert(dynamic_cast<Mob*>(&*sceneNode) != nullptr);
					static_cast<Mob&>(*sceneNode).setIdentifier(1);
				}
				mSceneGraph.attachChild(std::move(sceneNode));
			}
		}
	}

	void Overworld::loadTextures()
	{
		mTextures.load(TextureID::Entities, "res/img/entities.png");
	}

	void Overworld::loadNodeFactory()
	{
		std::function<SceneNode::Ptr()> redConstructor = [this]()
		{
			return SceneNode::Ptr(new Mob(0, Mob::Red, mTextures, Category::Player));
		};
		mNodeFactory.registerNode("Red", redConstructor);
	}

	void Overworld::draw()
	{
		mTarget.draw(mTileMap);
		mTarget.draw(mSceneGraph);
	}

	void Overworld::update(sf::Time dt)
	{
		while (!mCommandQueue.isEmpty())
			mSceneGraph.onCommand(mCommandQueue.pop(), dt);

		mSceneGraph.update(dt, mCommandQueue);
		mSceneGraph.resolveSceneCollisions(mSceneGraph);
	}

}
