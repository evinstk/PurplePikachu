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
		, mLayers(0)
		, mTileMaps()
		, mNumLayers(0)
		, mCommandQueue()
	{
		loadTextures();
		loadNodeFactory();
	}

	CommandQueue& Overworld::getCommandQueue()
	{
		return mCommandQueue;
	}

	void Overworld::loadTMX(const std::string& filename)
	{
		TMXParser parser;
		parser.load(filename);

		mLayers.clear();
		mNumLayers = parser.getNumLayers();
		mLayers.resize(mNumLayers);

		std::vector<sf::VertexArray> vertices;

		int width(parser.getWidth());
		int height(parser.getHeight());
		int tileWidth(parser.getTileWidth());
		int tileHeight(parser.getTileHeight());
		int tilesetWidth(parser.getTilesetWidth());
		TileLayers tileLayers(parser.getTileLayers());

		mTileMaps.clear();
		for (auto& tileMap : tileLayers)
		{
			TileMap::Ptr currMap(new TileMap());
			currMap->setMapData(width, height, tileWidth, tileHeight, tilesetWidth, tileMap.second);
			currMap->setScale(4.f, 4.f);
			currMap->loadTexture("res/img/tiles.png");
			mLayers[tileMap.first] = currMap.get();
			mTileMaps.push_back(std::move(currMap));
		}

		ObjectLayers objectLayers(parser.getObjectLayers());
		for (auto& objectLayer : objectLayers)
		{
			SceneNode::Ptr objectGroup(new SceneNode(0));
			mLayers[objectLayer.first] = objectGroup.get();
			objectGroup->setScale(4.f, 4.f);
			for (auto& object : objectLayer.second)
			{
				SceneNode::Ptr sceneNode = mNodeFactory.get(object.type);
				sceneNode->setPosition((float)object.x, (float)object.y);
				if (object.isPlayer)
				{
					assert(dynamic_cast<Mob*>(&*sceneNode) != nullptr);
					static_cast<Mob&>(*sceneNode).setIdentifier(1);
				}
				objectGroup->attachChild(std::move(sceneNode));
			}
			mSceneGraph.attachChild(std::move(objectGroup));
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
		for (auto& layer : mLayers)
		{
			mTarget.draw(*layer);
		}
	}

	void Overworld::update(sf::Time dt)
	{
		while (!mCommandQueue.isEmpty())
			mSceneGraph.onCommand(mCommandQueue.pop(), dt);

		mSceneGraph.update(dt, mCommandQueue);
		mSceneGraph.resolveSceneCollisions(mSceneGraph);
	}

}
