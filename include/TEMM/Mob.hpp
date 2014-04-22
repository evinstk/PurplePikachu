#ifndef TEMM_MOB_HPP
#define TEMM_MOB_HPP

#include <TEMM/SceneNode.hpp>
#include <TEMM/ResourceIdentifiers.hpp>
#include <TEMM/SpriteNode.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

namespace temm
{

	class Mob : public SceneNode
	{
	public:
		enum Type
		{
			Red,
			TypeCount
		};
		enum class Direction
		{
			None,
			Left,
			Right,
			Up,
			Down,
		};

		Mob(unsigned z, Type type, const TextureHolder& textures, Category::Type category = Category::None);

		sf::FloatRect getBoundingRect() const;

		void setDirection(Direction direction);
		void setIdentifier(int identifier);

		int getIdentifier() const;

	private:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void resolveCurrent(SceneNode& node);

		Type mType;
		int mIdentifier;
		sf::Sprite mCollisionSprite;
		SpriteNode* mHead;
		Direction mDirection;

		// Stepping members
		bool mStepping;
		bool mFirstStep;
		sf::Time mStepDelay;
		int mStepDistance;
		sf::Time mStepWait;
		int mDiffX;
		int mDiffY;
		int mDestX;
		int mDestY;
		int mOrigX;
		int mOrigY;
	};

}

#endif