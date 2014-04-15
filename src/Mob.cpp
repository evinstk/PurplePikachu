#include <TEMM/Mob.hpp>
#include <TEMM/DataTables.hpp>
#include <TEMM/ResourceHolder.hpp>

namespace temm
{

	namespace
	{
		const std::vector<MobData> Table = initializeMobData();
		const int HeadHeight = 3;
		const int CollisionHeight = 16;
	}

	Mob::Mob(unsigned z, Type type, const TextureHolder& textures)
		: SceneNode(z)
		, mType(type)
		, mCollisionSprite(textures.get(Table[type].texture))
		, mVelocity(0.f, 0.f)
	{
		sf::IntRect collisionRect = Table[type].textureRect;
		collisionRect.top = collisionRect.top + HeadHeight;
		collisionRect.height = CollisionHeight;
		mCollisionSprite.setTextureRect(collisionRect);

		sf::IntRect headRect = Table[type].textureRect;
		headRect.height = HeadHeight;
		std::unique_ptr<SpriteNode> head(new SpriteNode(z + 1, *mCollisionSprite.getTexture(), headRect));
		mHead = head.get();
		attachChild(std::move(head));
	}

}