#ifndef TEMM_MOB_HPP
#define TEMM_MOB_HPP

#include <TEMM/SceneNode.hpp>
#include <TEMM/ResourceIdentifiers.hpp>
#include <TEMM/SpriteNode.hpp>
#include <SFML/Graphics/Sprite.hpp>

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

		Mob(unsigned z, Type type, const TextureHolder& textures);

		sf::FloatRect getBoundingRect() const;

		void setVelocity(sf::Vector2f velocity);
		void setVelocity(float vx, float vy);

	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		Type mType;
		sf::Sprite mCollisionSprite;
		SpriteNode* mHead;
		sf::Vector2f mVelocity;
	};

}

#endif