#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include <TEMM/SceneNode.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace temm
{

	class SpriteNode : public SceneNode
	{
	public:
		explicit SpriteNode(const sf::Texture& texture);
		SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Sprite mSprite;
	};

}

#endif