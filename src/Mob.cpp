#include <TEMM/Mob.hpp>
#include <TEMM/DataTables.hpp>
#include <TEMM/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace temm
{

	namespace
	{
		const std::vector<MobData> Table = initializeMobData();
	}

	Mob::Mob(unsigned z, Type type, const TextureHolder& textures)
		: SceneNode(z)
		, mType(type)
		, mCollisionSprite(textures.get(Table[type].texture), Table[type].collisionRect)
		, mVelocity(0.f, 0.f)
	{
		MobData data = Table[type];
		std::unique_ptr<SpriteNode> head(new SpriteNode(z + 1, *mCollisionSprite.getTexture(), data.headRect));
		head->setPosition(0.f, -(float)data.headRect.height);
		mHead = head.get();
		attachChild(std::move(head));
	}

	sf::FloatRect Mob::getBoundingRect() const
	{
		return getWorldTransform().transformRect(mCollisionSprite.getGlobalBounds());
	}

	void Mob::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mCollisionSprite, states);
	}
}
