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

	Mob::Mob(unsigned z, Type type, const TextureHolder& textures, Category::Type category)
		: SceneNode(z, category)
		, mType(type)
		, mCollisionSprite(textures.get(Table[type].texture), Table[type].collisionRect)
		, mHead(nullptr)
		, mDirection(Direction::None)
		, mStepping(false)
		, mStepDelay(sf::seconds(0.5))
		, mStepDistance(16)
		, mStepWait(sf::Time::Zero)
		, mDiffX(0)
		, mDiffY(0)
		, mDestX(0)
		, mDestY(0)
		, mOrigX(0)
		, mOrigY(0)
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

	void Mob::setDirection(Direction direction)
	{
		mDirection = direction;
	}

	void Mob::setIdentifier(int identifier)
	{
		mIdentifier = identifier;
	}

	int Mob::getIdentifier() const
	{
		return mIdentifier;
	}

	void Mob::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		mStepWait -= dt;
		if (mStepWait < sf::Time::Zero) mStepWait = sf::Time::Zero;

		if (mStepping)
		{
			sf::Vector2f currPos = getPosition();
			currPos.x += mDiffX * dt.asSeconds() / mStepDelay.asSeconds();
			currPos.y += mDiffY * dt.asSeconds() / mStepDelay.asSeconds();
			setPosition(currPos);
		}

		if (mStepWait > sf::Time::Zero)
		{
			mDirection = Direction::None;
			return;
		}

		if (mStepping)
		{
			setPosition((float)mDestX, (float)mDestY);
		}
		mStepping = false;

		mDiffX = 0;
		mDiffY = 0;

		if (mDirection == Direction::Left)
		{
			mDiffX = -mStepDistance;
		}
		else if (mDirection == Direction::Right)
		{
			mDiffX = mStepDistance;
		}
		else if (mDirection == Direction::Up)
		{
			mDiffY = -mStepDistance;
		}
		else if (mDirection == Direction::Down)
		{
			mDiffY = mStepDistance;
		}

		sf::Vector2f currPos = getPosition();
		if (mDiffY || mDiffX)
		{
			mStepping = true;
			mDestX = (int)currPos.x + mDiffX;
			mDestY = (int)currPos.y + mDiffY;
			mStepWait = mStepDelay;
		}
		mOrigX = (int)currPos.x;
		mOrigY = (int)currPos.y;
		mDirection = Direction::None;
	}

	void Mob::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mCollisionSprite, states);
	}

	void Mob::resolveCurrent(SceneNode& node)
	{
		unsigned int category = node.getCategory();

		if (category & Category::Character && this != &node && collides(node))
		{
			mStepping = false;
			setPosition((float)mOrigX, (float)mOrigY);
			mStepWait = sf::Time::Zero;
		}
	}
}
