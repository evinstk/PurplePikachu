#include <TEMM/SpriteNode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace temm
{

	SpriteNode::SpriteNode(unsigned z, const sf::Texture& texture)
		: SceneNode(z)
		, mSprite(texture)
	{
	}

	SpriteNode::SpriteNode(unsigned z, const sf::Texture& texture, const sf::IntRect& textureRect)
		: SceneNode(z)
		, mSprite(texture, textureRect)
	{
	}

	void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mSprite, states);
	}

}